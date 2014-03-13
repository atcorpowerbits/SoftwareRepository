/*
 * \file
 *
 * \brief Interface to DataFlash storage
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 31/05/2013 10:09:27 PM
 * \author victora
 */ 


#ifndef DATAFLASH_IF_H_
#define DATAFLASH_IF_H_

//_____ D E F I N I T I O N S ______________________________________________

/*! \name AT45DBX Group A Commands
 */
//! @{
#define AT45DBX_CMDA_RD_PAGE              0xD2        //!< Main Memory Page Read (Serial/8-bit Mode).
#define AT45DBX_CMDA_RD_ARRAY_LEG         0xE8        //!< Continuous Array Read, Legacy Command (Serial/8-bit Mode).
#define AT45DBX_CMDA_RD_ARRAY_LF_SM       0x03        //!< Continuous Array Read, Low-Frequency Mode (Serial Mode).
#define AT45DBX_CMDA_RD_ARRAY_AF_SM       0x0B        //!< Continuous Array Read, Any-Frequency Mode (Serial Mode).
#define AT45DBX_CMDA_RD_SECTOR_PROT_REG   0x32        //!< Read Sector Protection Register (Serial/8-bit Mode).
#define AT45DBX_CMDA_RD_SECTOR_LKDN_REG   0x35        //!< Read Sector Lockdown Register (Serial/8-bit Mode).
#define AT45DBX_CMDA_RD_SECURITY_REG      0x77        //!< Read Security Register (Serial/8-bit Mode).
//! @}

/*! \name AT45DBX Group B Commands
 */
//! @{
#define AT45DBX_CMDB_ER_PAGE              0x81        //!< Page Erase (Serial/8-bit Mode).
#define AT45DBX_CMDB_ER_BLOCK             0x50        //!< Block Erase (Serial/8-bit Mode).
#define AT45DBX_CMDB_ER_SECTOR            0x7C        //!< Sector Erase (Serial/8-bit Mode).
#define AT45DBX_CMDB_ER_CHIP              0xC794809A  //!< Chip Erase (Serial/8-bit Mode).
#define AT45DBX_CMDB_XFR_PAGE_TO_BUF1     0x53        //!< Main Memory Page to Buffer 1 Transfer (Serial/8-bit Mode).
#define AT45DBX_CMDB_XFR_PAGE_TO_BUF2     0x55        //!< Main Memory Page to Buffer 2 Transfer (Serial/8-bit Mode).
#define AT45DBX_CMDB_CMP_PAGE_TO_BUF1     0x60        //!< Main Memory Page to Buffer 1 Compare (Serial/8-bit Mode).
#define AT45DBX_CMDB_CMP_PAGE_TO_BUF2     0x61        //!< Main Memory Page to Buffer 2 Compare (Serial/8-bit Mode).
#define AT45DBX_CMDB_PR_BUF1_TO_PAGE_ER   0x83        //!< Buffer 1 to Main Memory Page Program with Built-in Erase (Serial/8-bit Mode).
#define AT45DBX_CMDB_PR_BUF2_TO_PAGE_ER   0x86        //!< Buffer 2 to Main Memory Page Program with Built-in Erase (Serial/8-bit Mode).
#define AT45DBX_CMDB_PR_BUF1_TO_PAGE      0x88        //!< Buffer 1 to Main Memory Page Program without Built-in Erase (Serial/8-bit Mode).
#define AT45DBX_CMDB_PR_BUF2_TO_PAGE      0x89        //!< Buffer 2 to Main Memory Page Program without Built-in Erase (Serial/8-bit Mode).
#define AT45DBX_CMDB_PR_PAGE_TH_BUF1      0x82        //!< Main Memory Page Program through Buffer 1 (Serial/8-bit Mode).
#define AT45DBX_CMDB_PR_PAGE_TH_BUF2      0x85        //!< Main Memory Page Program through Buffer 2 (Serial/8-bit Mode).
#define AT45DBX_CMDB_RWR_PAGE_TH_BUF1     0x58        //!< Auto Page Rewrite through Buffer 1 (Serial/8-bit Mode).
#define AT45DBX_CMDB_RWR_PAGE_TH_BUF2     0x59        //!< Auto Page Rewrite through Buffer 2 (Serial/8-bit Mode).
//! @}

/*! \name AT45DBX Group C Commands
 */
//! @{
#define AT45DBX_CMDC_RD_BUF1_LF_SM        0xD1        //!< Buffer 1 Read, Low-Frequency Mode (Serial Mode).
#define AT45DBX_CMDC_RD_BUF2_LF_SM        0xD3        //!< Buffer 2 Read, Low-Frequency Mode (Serial Mode).
#define AT45DBX_CMDC_RD_BUF1_AF_SM        0xD4        //!< Buffer 1 Read, Any-Frequency Mode (Serial Mode).
#define AT45DBX_CMDC_RD_BUF2_AF_SM        0xD6        //!< Buffer 2 Read, Any-Frequency Mode (Serial Mode).
#define AT45DBX_CMDC_RD_BUF1_AF_8M        0x54        //!< Buffer 1 Read, Any-Frequency Mode (8-bit Mode).
#define AT45DBX_CMDC_RD_BUF2_AF_8M        0x56        //!< Buffer 2 Read, Any-Frequency Mode (8-bit Mode).
#define AT45DBX_CMDC_WR_BUF1              0x84        //!< Buffer 1 Write (Serial/8-bit Mode).
#define AT45DBX_CMDC_WR_BUF2              0x87        //!< Buffer 2 Write (Serial/8-bit Mode).
#define AT45DBX_CMDC_RD_STATUS_REG        0xD7        //!< Status Register Read (Serial/8-bit Mode).
#define AT45DBX_CMDC_RD_MNFCT_DEV_ID_SM   0x9F        //!< Manufacturer and Device ID Read (Serial Mode).
//! @}

/*! \name AT45DBX Group D Commands
 */
//! @{
#define AT45DBX_CMDD_EN_SECTOR_PROT       0x3D2A7FA9  //!< Enable Sector Protection (Serial/8-bit Mode).
#define AT45DBX_CMDD_DIS_SECTOR_PROT      0x3D2A7F9A  //!< Disable Sector Protection (Serial/8-bit Mode).
#define AT45DBX_CMDD_ER_SECTOR_PROT_REG   0x3D2A7FCF  //!< Erase Sector Protection Register (Serial/8-bit Mode).
#define AT45DBX_CMDD_PR_SECTOR_PROT_REG   0x3D2A7FFC  //!< Program Sector Protection Register (Serial/8-bit Mode).
#define AT45DBX_CMDD_LKDN_SECTOR          0x3D2A7F30  //!< Sector Lockdown (Serial/8-bit Mode).
#define AT45DBX_CMDD_PR_SECURITY_REG      0x9B000000  //!< Program Security Register (Serial/8-bit Mode).
#define AT45DBX_CMDD_PR_CONF_REG          0x3D2A80A6  //!< Program Configuration Register (Serial/8-bit Mode).
#define AT45DBX_CMDD_DEEP_PWR_DN          0xB9        //!< Deep Power-down (Serial/8-bit Mode).
#define AT45DBX_CMDD_RSM_DEEP_PWR_DN      0xAB        //!< Resume from Deep Power-down (Serial/8-bit Mode).
//! @}

/*! \name Bit-Masks and Values for the Status Register
 */
//! @{
#define AT45DBX_MSK_BUSY                  0x80        //!< Busy status bit-mask.
#define AT45DBX_BUSY                      0x00        //!< Busy status value (0x00 when busy, 0x80 when ready).
#define AT45DBX_MSK_DENSITY               0x3C        //!< Device density bit-mask.
//! @}

/*! \brief Sends a dummy byte through SPI.
 */
#define spi_write_dummy()                 spi_write(AT45DBX_SPI, 0xFF)

#ifdef _NEW_DATAFLASH // New DataFlash chip is AT45DB641E used for NUTMEG

#define DF_PAGE_SIZE           (264) // Standard DataFlash page size in bytes
#define DF_PAGE_STEP           (512) // Step to next page address in DataFlash is 512B per page when Std DataFlash page size is used
#define DF_PAGES_PER_BLOCK     (8)
#define DF_MAX_BLOCKS          (4096)

#else

#define DF_PAGE_SIZE           (1056) // Standard DataFlash page size in bytes
#define DF_PAGE_STEP           (2048) // Step to next page address in DataFlash is 2KB per page when Std DataFlash page size is used
#define DF_PAGES_PER_BLOCK     (8)
#define DF_MAX_BLOCKS          (1024)

#endif

#define DF_PAGES_PER_CBP_PARAM	(uint16_t)((sizeof(rec_cbp_t) + DF_PAGE_SIZE - 1) / DF_PAGE_SIZE) // CBP measurement parameters (without raw cuff signal)
#define DF_PAGES_PER_RAW_SIGNAL	(uint16_t)((sizeof(uint16_t)*CAPTURE_SIZE + DF_PAGE_SIZE - 1) / DF_PAGE_SIZE)

#define DF_MAX_PAGES           (DF_MAX_BLOCKS * DF_PAGES_PER_BLOCK)
#define DF_MAX_BYTES           (DF_MAX_PAGES * DF_PAGE_SIZE) // Standard DataFlash size
#define DF_PAGE_ADDR_OVERFLOW  (DF_MAX_PAGES * DF_PAGE_STEP)

#define DF_CBP_START_PAGE	   (uint16_t)(DF_MAX_PAGES / 2) // Half of total DataFlash pages
#define DF_PAGES_PER_CBP_MEAS  (DF_PAGES_PER_CBP_PARAM + DF_PAGES_PER_RAW_SIGNAL) // Total pages per CBP measurement including raw cuff signal

#define DF_LOG_START_PAGE	   (uint16_t)(CBP_MAX_MEASUREMENTS * DF_PAGES_PER_CBP_MEAS + DF_CBP_START_PAGE)
#define DF_LOG_MAX_PAGES	   (uint16_t)(DF_POST_PAGE_NUMBER - DF_LOG_START_PAGE) // Logging space ends before the POST of DataFlash page

#define DF_LOG_DATA_START_INDEX		(uint8_t)(4) // First 2 bytes for data_index, second 2 bytes for page_number, so data area starts from index 4.

#define MEAS_BRACHIAL_WAVEFORM_LEN (MEAS_DEFAULT_SAMPLE_RATE * PWA_MAX_CAPTURE_TIME)

#define CBP_REC_CHECKSUM_LEN   (2) // for modulo 16 bits CRC.
#define CBP_MAX_MEASUREMENTS   (500)
#define CBP_CONFIG_PAGE        (DF_MAX_PAGES - 1) // CBP config bytes are saved in the last page
#define DF_POST_PAGE_NUMBER    (DF_MAX_PAGES - 2) // One page just before config page for POST data flash test.

// DataFlash related errors
typedef enum
{
	DF_RW_SUCCESS = 0,
	DF_WRITING_TOO_MANY_DATA = 4001,
	DF_READING_TOO_MANY_DATA,
	DF_COMMIT_RAW_CUFF_SIGNAL_FAILED,
	DF_COMMIT_CBP_REC_FAILED,
	DF_MEAS_REC_OVERFLOW,
	DF_COMMIT_RAW_CUFF_SIGNAL_NOT_AVAILABLE,
	DF_RW_TASK_FAILED,
	DF_MEAS_INDEX_INVALID,
	DF_READ_REC_CHECKSUM_FAILED,
	DF_READ_LOG_REC_FAILED,
	DF_WRITE_LOG_REC_FAILED,
	DF_BUFFER_OUT_OF_MEMORY,
	DF_READ_CONFIG_REC_FAILED,
	DF_WRITE_CONFIG_REC_FAILED,
	DF_CONFIG_REC_NOT_LOADED,
	DF_CBP_REC_FORMAT_INCOMPATIBLE,
	DF_READ_AFTER_WRITE_VERIFICATION_FAILED,
	DF_SPI_MASTER_INIT_FAILED,
	DF_SPI_MASTER_MODE_FAILED,
	DF_SPI_MASTER_FAILED,
	DF_SPI_SLAVE_INIT_FAILED,
	DF_SPI_SLAVE_FAILED,
	DF_SPI_READ_FAILED,
	DF_SPI_WRITE_FAILED,
	DF_READ_OPEN_FAILED,
	DF_READ_PAGE_FAILED,
	DF_READ_MULTI_PAGE_FAILED,
	DF_WRITE_OPEN_FAILED,
	DF_WRITE_PAGE_FAILED,
	DF_DELAYED_WRITE_PAGE_FAILED,
	DF_WRITE_MULTI_PAGE_FAILED,
	DF_GPIO_NOT_ENABLED,
	DF_INIT_FAILED,
	DF_READ_ID_FAILED,
	DF_WAIT_READY_FAILED,
	DF_CLOSE_FAILED,
	DF_ERASE_PAGE_FAILED,
	DF_WRITE_PAGE_NODE_FAILED,
	DF_WRITE_PAGE_COPY_FAILED,
	DF_RETRIEVE_CBP_REC_FAILED,
} df_error_code_t;

typedef struct
{
	uint8_t manufacturer_id;
	uint8_t device_id_1;
	uint8_t device_id_2;
	uint8_t ext_info_len;
} df_id_t;

// DF write page queue node
typedef struct _df_write_page_node *df_write_page_node_ptr;
typedef struct _df_write_page_node
{
	uint16_t page_number;
	uint8_t *data_copy;
	uint16_t data_size;
	df_write_page_node_ptr next;
} df_write_page_node;

extern void enque_df_write_page (df_write_page_node *new_page);
extern df_write_page_node * deque_df_write_page (void);

extern void rw_data_flash_task (void);
extern void df_interface_init();

extern df_error_code_t df_read_open (uint32_t df_page_addr);
extern df_error_code_t df_write_open (uint32_t df_page_addr);
extern df_error_code_t df_read_page (uint16_t df_page_num, uint8_t *data_dest, uint16_t size_to_read);
extern df_error_code_t df_write_page (uint16_t df_page_num, uint8_t *data_source, uint16_t size_to_write);
extern df_error_code_t df_read_multiple_pages (uint16_t df_page_num, uint8_t *data_dest, uint16_t size_to_read);
extern df_error_code_t df_write_multiple_pages (uint16_t df_page_num, uint8_t *data_source, uint16_t size_to_write);
extern df_error_code_t df_erase_page (uint16_t page_num);
extern df_error_code_t df_close (void);
extern void df_chipselect (bool bSelect);
extern df_error_code_t df_wait_ready (void);
extern bool df_spi_master (void);
extern bool df_spi_slave (void);
extern void df_display_id (void);

#endif /* DATAFLASH_IF_H_ */