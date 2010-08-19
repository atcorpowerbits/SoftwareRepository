# File: msrw.py
# Description: My serial read write
# History:
#   v0.1    12 Aug 2010     LC      Original
#
import sys, threading, string, serial, time
from crc_algorithms import Crc
from array import array
import argparse

if __name__ == '__main__'  and (sys.version_info < (2, 7) or sys.version_info >= (3, 0)):
    sys.stderr.write("""\
==============================================================================
WARNING: this code has only been tested on Python 2.7.
This seems to be an different version of Python running.
Continuing anyway...
==============================================================================
""")
    
# Packet definitions used in the input file.
COMMAND_FIELD_POS = 0
LENGTH_FIELD_POS = 1

# Command definitions used in the input file.
COMMENT_CHR = '#'
PAUSE_CHR = 'p'
PAUSE_LEN = 2
C_SEND_CHR = 'm'
C_SEND_LEN = 2
NO_CRC_CHR = 'r'
NO_CRC_LEN = 1
WAIT_RX_CHR = 'w'
WAIT_RX_LEN = 1
LAST_PKT_CHR = 'l'
LAST_PKT_LEN = 1

# Description: This class encapsulates methods for the input file.
class inputfile:
    def __init__(self,fname):
        self.fh = open(fname)
        self.lines=self.fh.readlines()
        self.nlines = len(self.lines)
    def dump(self):
        for line in self.lines:
            print line
    def wait(self,sec):             # wait for number of seconds
        time.sleep(sec)
    def lines():
        return self.lines
##    def bsplit(self):           # byte split
##        for line in self.lines:
##            word = line.split()
##            for data in word:
##                i = int(data,16)
##                print hex(i)

# Description: This class encapsulates methods for the received packet.
# Comments: create pkt from list, ie. []
class rxPkt:
    def __init__(self, aFi):
        self.p = []
        self.fi = aFi
    def reset(self):
        self.p[:] = []
    def append(self, it):
        self.p.append(it)
    def proper(self):
        ok = False
        pLen = len(self.p)
        if pLen > 2:
            if pLen-1 == self.p[LENGTH_FIELD_POS]:
                if self.crcOk():
                    ok = True                    
        return ok
    def dump(self):
        print self.p
    def crcOk(self):
        crc = Crc(width=8,poly=0x07,reflect_in=False,xor_in=0x00,reflect_out=False,xor_out=0x00)
        s = str()
        for i in self.p[0:-1]:
            s += chr(i)
        cVal = crc.table_driven(s)
        sys.stdout.write("rx ")
        self.fi.write("rx ")
        if self.p[-1] == cVal:
            for i in self.p:
                sys.stdout.write("0x%x " % i)
                self.fi.write("0x%x " % i)
            sys.stdout.write('\n')
            self.fi.write('\n')
##            sys.stdout.write("rx %s\n" % self.p)
##            self.fi.write("rx %s\n" % self.p)  # log to file
            ok = True
        else:
            sys.stdout.write("rx %s incorrect crc\n")
            self.fi.write("rx %s\n incorrect crc" % self.p)  # log to file
            ok = False
        self.reset()
        return ok

# Description: calculate CRC8
def calCrc(s):
        crc = Crc(width=8,poly=0x07,reflect_in=False,xor_in=0x00,reflect_out=False,xor_out=0x00)
        cVal = crc.table_driven(s)
        # sys.stdout.write("%s 0x%0x\n" % (s, cVal))     # print crc value
        return cVal

# Description: This class encapsulates the actions of the ReadThread.
class ReadThread(threading.Thread):
    def __init__(self, aSe, aWs, aRs, aFi):
        # Arguments:
        # aSe: serial port, aRs: read semaphore, aWs: write semaphore, aFi: output file object
        threading.Thread.__init__(self)
        self.se = aSe
        self.ws = aWs
        self.rs = aRs
        self.fi = aFi
        sys.stdout.write("ReadThread init\n")
    def run(self):
        sys.stdout.write("ReadThread run\n")
        p = rxPkt(self.fi)
        self.rs.wait()
        while self.rs.isWaiting():
            while self.se.inWaiting() > 0:                
                data = self.se.read()   # read 1 character at a time
                for character in data:
                    b = character.encode('hex') # escape everything, hex dump
                p.append(int(b,16)) # convert string to hex numbers
                if p.proper():
                    self.ws.signal()               
        time.sleep(2)       # arbitrary sleep time, can be removed.
        sys.stdout.write("ReadThread completed\n")

# Description: My own error class
class MyError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

# Description: This class encapsulates the actions of the WriteThread.
class WriteThread(threading.Thread):
    def __init__(self, aSe, aWs, aRs, aFi, aOutFi):
        # Arguments:
        # aSe: serial port, aRs: read semaphore, aWs: write semaphore,
        # aFi: input file object, aOutFi: output file object
        threading.Thread.__init__(self)
        sys.stdout.write("WriteThread init\n")
        self.se = aSe
        self.ws = aWs
        self.rs = aRs
        self.fi = aFi
        self.outFi = aOutFi
    def run(self):
        cSend = False # continuous send
        cSendPeriod = 0.0 # continuous send period
        doCrc = True
        lastPkt = False
        sys.stdout.write("WriteThread run\n")

        try:
            # Send(self.fi, se)
            for line in self.fi.lines:
                # send command
                word = line.split()
                if len(word) > 0:
                    if word[COMMAND_FIELD_POS][0] == COMMENT_CHR:
                        # if first char of first word is COMMENT_CHR, ...
                        # sys.stdout.write("comment, ignore\n")
                        pass
                    elif str.lower(word[COMMAND_FIELD_POS]) == PAUSE_CHR:
                        # pause for (word[1]) number of seconds
                        if len(word) == PAUSE_LEN:
                            waitTime = float(word[1])
                            sys.stdout.write("pause %f secs\n" % waitTime)
                            time.sleep(waitTime)
                        else:
                            raise MyError("Invalid pause format. Usage: '{0} 0.1'".format(PAUSE_CHR))
                    elif str.lower(word[COMMAND_FIELD_POS]) == C_SEND_CHR:
                        # send continuous data, with (word[1]) number of msec between packets
                        if len(word) == C_SEND_LEN:
                            if cSend == False:
                                cSend = True
                                cSendPeriod = float(word[1])
                            else:
                                cSend = False
                                cSendPeriod = 0.0
                        else:
                            raise MyError("Invalid continuous send format. Usage: '{0} 0.004 or {0} 0'".format(C_SEND_CHR))                       
                    elif str.lower(word[COMMAND_FIELD_POS]) == NO_CRC_CHR:
                        # toggle calculate crc
                        if len(word) == NO_CRC_LEN:
                            doCrc = not doCrc
                        else:
                            raise MyError("Invalid calc CRC format. Usage: '{0}'".format(NO_CRC_CHR))
                    elif str.lower(word[0]) == WAIT_RX_CHR:
                        # wait for a rx packet
                        if len(word) == WAIT_RX_LEN:
                            # wait for response
                            self.ws.wait()
                            while self.ws.isWaiting():
                                continue
                        else:
                            raise MyError("Invalid wait format. Usage: '{0}'".format(WAIT_RX_CHR))
                    elif str.lower(word[0]) == LAST_PKT_CHR:
                        # next packet will be the last, application can quite once it has been sent
                        if len(word) == LAST_PKT_LEN:
                            lastPkt = True
                        else:
                            raise MyError("Invalid last packet format. Usage: '{0}'".format(LAST_PKT_CHR))
                    else:
                        if len(word) < 3:
                            if len(word) >= 2 and word[LENGTH_FIELD_POS] < 3:
                                raise MyError("tx incorrect packet length")
                            else:
                                raise MyError("tx packet length < 3")
                                                
                        # actual data to be sent
                        s = str()                    
                        sys.stdout.write("tx ")
                        self.outFi.write("tx ")
                        for data in word:
                            s += data
                            i = int(data,16)
                            sys.stdout.write("%s " % hex(i))
                            self.outFi.write("%s " % hex(i))
                            self.se.write(chr(i))
                            self.se.flush()          # wait for data to be written
                        if doCrc:
                            cVal = calCrc(s.decode("hex"))
                            sys.stdout.write("0x%x" % cVal)
                            self.outFi.write("0x%x" % cVal)
                            self.se.write(chr(cVal))
                            self.se.flush()
                        sys.stdout.write('\n')
                        self.outFi.write('\n')
                        
                        if not cSend:
                            if not lastPkt:
                                # wait for response
                                self.ws.wait()
                                while self.ws.isWaiting():
                                    continue
                        else:
                            # wait for cSendPeriod, and continue to send
                            time.sleep(cSendPeriod)
                # else ignore empty lines
            
            time.sleep(1)       # arbitrary sleep time, can be removed
            self.rs.signal()     # signal reading thread
            sys.stdout.write("WriteThread completed\n")
        except MyError as e:
            self.rs.signal()     # signal reading thread
            sys.stderr.write("%s\n" % e)
            sys.stderr.write("WriteThread terminated abnormally\n")
            self.outFi.write("%s\n" % e)

# Description: Semaphore class to synchronise read and write threads.
# Comments: As an improvement, should look at using python built-in mutex operations
class Sem():                # semaphore
    def __init__(self):
        self.block = True
    def wait(self):
        self.block = True
    def isWaiting(self):
        return self.block
    def signal(self):
        self.block = False

# Description: Test CRC16 calculation
# Comments: Internal test function. Not used for actual send or receive operations.
def TestCrc16():
    crc = Crc(width=16,poly=0x8005,reflect_in=True,xor_in=0xffff,reflect_out=True,xor_out=0x0000)
    data = "01020304A12B".decode("hex")
    my_crc = crc.bit_by_bit_fast(data)
    print "0x%04x" % my_crc
    data2 = "01020304A12B"
    my_crc2 = crc.table_driven(data)
    print "0x%04x" % my_crc2

# Description: Test CRC8 calculation
# Comments: Internal test function. Not used for actual send or receive operations.
def TestCrc8():
    crc = Crc(width=8,poly=0x07,reflect_in=False,xor_in=0x00,reflect_out=False,xor_out=0x00)

    data = "400301".decode("hex")
    my_crc = crc.bit_by_bit_fast(data) 
    print "0x%04x" % my_crc

    data2 = [0x40,0x03,0x01]          # crc of [1,3,1]==0x53, [0x40,3,1]==0xbe
    print r"data2[-1]=0x%x" % data2[-2]
    s = str()
    for i in data2[:]:
        s += chr(i)
    my_crc2 = crc.table_driven(s)
    print "s=%s" % s
    print "crc2=0x%04x" % my_crc2

    data = "400301".decode("hex")
    my_crc = crc.table_driven(data)
    print "s=%s" % data
    print "crc3=0x%04x" % my_crc

    data4 = "00010203040506".decode("hex")
    my_crc4 = crc.table_driven(data4)
    print "s=%s" % data4
    print "crc4=0x%04x" % my_crc4

    data5 = "040506070809".decode("hex")
    my_crc5 = crc.table_driven(data5)
    print "s=%s" % data5
    print "crc4=0x%04x" % my_crc5

    data6 = "0506070809".decode("hex")
    my_crc6 = crc.table_driven(data6)
    print "s=%s" % data6
    print "crc4=0x%04x" % my_crc6

    data7 = "0A0B0C0D0E".decode("hex")
    my_crc7 = crc.table_driven(data7)
    print "s=%s" % data7
    print "crc4=0x%04x" % my_crc7

    data = "00070203040506".decode("hex")
    my_crc = crc.table_driven(data)
    print "s=%s" % data
    print "crc4=0x%04x" % my_crc

   
# Description: Test python array functions
# Comments: Internal test function. Not used for actual send or receive operations.
def TestArray():
    p = array('B')
    p.append(0x01)
    p.append(0x03)
    p.append(0x01)
    p.append(0x00)
    print len(p)
    print p[0], p[1], p[2], p[-1]
    s = p.tostring()
    print s
    l = p.tolist()
    print l
    # how to clear array?

# Description: Send file over serial port.
# Comments: Internal test function. Not used for actual send or receive operations.
def Send(file, se):          # send data to serial port
    for line in file.lines:
        word = line.split()
        for data in word:
            i = int(data,16)
            # sys.stdout.write("%s " % hex(i))
            se.write(chr(i))

# Description: main function
def main():
    sys.stdout.write("main started ...\n")

    parser = argparse.ArgumentParser(description='Send EM4 commands & record transactions')
    parser.add_argument('-i', dest='inStr', default=r"c:\pythoncodes\z", help='inputFile')
    parser.add_argument('-o', dest='outStr', default=r"c:\pythoncodes\a", help='outputFile')
    parser.add_argument('-t', dest='testMode', action='store_true', help='enable test mode')
    parser.add_argument('-c', dest='comport', default='COM1', help='com port')
    parser.add_argument('-b', dest='baud', type=int, default=115200, help='baud rate')
    args = parser.parse_args()
    # print "in=%s out=%s test=%d baud=%d" % (args.inStr, args.outStr, args.testMode, args.baud)

    if args.testMode:
        TestCrc8()
    else:    
        ws = Sem()
        rs = Sem() 
        infile = inputfile(args.inStr)
        outfile = open(args.outStr, 'w')

        try:
            sys.stdout.write("open %s at %dbps\n" % (args.comport, args.baud))
            se = serial.Serial(args.comport, args.baud)    # auto opened if successful

            read = ReadThread(se, ws, rs, outfile)
            read.start()

            write = WriteThread(se, ws, rs, infile, outfile)
            write.start()

            read.join()
            write.join()

            se.close()
        except serial.SerialException:
            sys.stderr.write("cannot be opened\n")

        # python appears to close opened files properly here.

        sys.stdout.write("Main program waited until read and write were done.\n")

if __name__ == '__main__':
    main()
