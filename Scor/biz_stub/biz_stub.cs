using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using AtCor.Scor.DataAccess;

namespace biz_stub
{
    /**This class is a stub to be used in place of the biz.dll.
     */ 
    public class BizStub_BizSession
    {
        /**This method will return true or false dependeing upon the random number generated.
         */ 
        public bool CheckIfDeviceConnected()
        {
            bool flag = true;
            Random random = new Random();
            int value = random.Next(0, 5);

            flag = value == 0 ? false : true;
            return flag;          
        }

        /** This method returns value Default for security mode
         * */
        public string GetSecurityMode()
        {
            return "Default";
        }

        /** This method takes a reference string as parameter to find electronic module
         * */
        public int FindModule(ref string portName)
        {
            DalModule d = DalModule.Instance;
            int returnValue = d.FindModule(portName);

            return returnValue;
        }

        /** This method returns text file name with full path which is saved after report calculation
         * */
        public string GetSavedFileName()
        { 
            DalModule dalMod = DalModule.Instance;
            return dalMod.GetSavedFilePath();
        }
    }
}
