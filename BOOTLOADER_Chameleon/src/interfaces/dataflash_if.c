/*
 * \file
 *
 * \brief Interface to DataFlash storage
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 31/05/2013 10:09:51 PM
 * \author victora
 */ 

#include <gpio.h>
#include <board.h>
#include <spi.h>
#include <sysclk.h>
#include <string.h> // for memcpy
#include <usart.h>
#include "print_funcs.h"
#include "conf_at45dbx.h"
#include "dataflash_if.h"
#include "usart_if.h"

//#if BOARD == OSCAR_ALPHA
  //// Oscar board SPI0 GPIO pins which are not compatible with NUTMEG board
  //static const gpio_map_t AT45DBX_SPI_GPIO_MAP =
  //{
	//{AVR32_SPI0_SCK_PIN,          AVR32_SPI0_SCK_FUNCTION         },  // SPI Clock.
	//{AVR32_SPI0_MISO_PIN,         AVR32_SPI0_MISO_FUNCTION        },  // MISO.
	//{AVR32_SPI0_MOSI_PIN,         AVR32_SPI0_MOSI_FUNCTION        },  // MOSI.
	//{AVR32_SPI0_NPCS_1_4_PIN,     AVR32_SPI0_NPCS_1_4_FUNCTION    },  // SPI0 Chip Select NPCS[1]
  //};
//#elif BOARD == NUTMEG_BOARD
  //// Nutmeg board SPI1 GPIO pins which are not compatible with UC3C_EK
  static const gpio_map_t AT45DBX_SPI_GPIO_MAP =
  {
	{AVR32_SPI1_SCK_PIN,          AVR32_SPI1_SCK_FUNCTION         },  // SPI Clock.
	{AVR32_SPI1_MISO_PIN,         AVR32_SPI1_MISO_FUNCTION        },  // MISO.
	{AVR32_SPI1_MOSI_PIN,         AVR32_SPI1_MOSI_FUNCTION        },  // MOSI.
	{AVR32_SPI1_NPCS_1_PIN,       AVR32_SPI1_NPCS_1_FUNCTION      },  // SPI1 Chip Select NPCS[1]
  };
//#else
  //// Original SPI1 GPIO pins for UC3C_EK
  //static const gpio_map_t AT45DBX_SPI_GPIO_MAP =
  //{
    //{AT45DBX_SPI_SCK_PIN,          AT45DBX_SPI_SCK_FUNCTION         },  // SPI Clock.
    //{AT45DBX_SPI_MISO_PIN,         AT45DBX_SPI_MISO_FUNCTION        },  // MISO.
    //{AT45DBX_SPI_MOSI_PIN,         AT45DBX_SPI_MOSI_FUNCTION        },  // MOSI.
    //{AT45DBX_SPI_NPCS0_PIN,        AT45DBX_SPI_NPCS0_FUNCTION       },  // SPI1 Chip Select NPCS[1]
  //};
//#endif

// SPI options.
spi_options_t spiOptions =
{
	.reg          = AT45DBX_SPI_FIRST_NPCS,   // Defined in conf_at45dbx.h.
	.baudrate     = AT45DBX_SPI_MASTER_SPEED, // Defined in conf_at45dbx.h.
	.bits         = AT45DBX_SPI_BITS,         // Defined in conf_at45dbx.h.
	.spck_delay   = 0,
	.trans_delay  = 0,
	.stay_act     = 1,
	.spi_mode     = 0,
	.modfdis      = 1
};

// Remember when Data Flash is opened to avoid opening it again
static bool df_is_opened = false;

// CBP DF write page queue (FIFO) to avoid race condition
static df_write_page_node *df_write_page_head = NULL;

/**
 * \brief Add a DF page to DF write page queue (FIFO)
 * \param[in] new_page New DF page to be written
 */
void enque_df_write_page (df_write_page_node *new_node)
{
	if (NULL == df_write_page_head)
	{
		df_write_page_head = new_node;
	}
	else
	{
		// Add the new page to write at the end of the queue by
		// walking to the end of DF write page queue
		df_write_page_node *node2node = df_write_page_head;
		
		while(node2node->next != NULL)
		{
			node2node = node2node->next;
		}
		node2node->next = new_node;
	}
}

/**
 * \brief Remove a DF write page from the head of DF write page queue (FIFO)
 * \return Next DF write page to be written; 
 * \retval NULL no more page to write
 */
df_write_page_node * deque_df_write_page (void)
{
	df_write_page_node *next_node = df_write_page_head;
	
	// Move the head of the queue to the next node
	if (df_write_page_head != NULL)
	{
		df_write_page_head = df_write_page_head->next;
	}
	return next_node;
}

/*! \brief Initializes the data flash controller and the SPI channel by which
 *         the DF is controlled.
 *
 * \param spiOptions  Initialization options of the DF SPI channel.
 * \param pba_hz      SPI module input clock frequency (PBA clock, Hz).
 *
 * \retval true Success.
 * \retval false Failure.
 */
bool df_init (spi_options_t spiOptions, unsigned int pba_hz)
{
	// Setup SPI registers according to spiOptions.
	if (spi_setupChipReg(AT45DBX_SPI, &spiOptions, pba_hz) != SPI_OK) 
	{
		return false;
	}
	return true;
}

/*! \brief Set to become SPI master
 *  \retval True It is now SPI master
 *  \retval False It failed to become SPI master
 */
bool df_spi_master (void)
{
	spi_status_t spi_status;
	uint32_t gpio_status;
	bool df_status;
	
	spi_disable(AT45DBX_SPI);
	gpio_status = gpio_enable_module(AT45DBX_SPI_GPIO_MAP,
                       sizeof(AT45DBX_SPI_GPIO_MAP) / sizeof(AT45DBX_SPI_GPIO_MAP[0]));
	if (GPIO_SUCCESS != gpio_status)
	{
		// Log the error details and return failure
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_GPIO_NOT_ENABLED);
		print_dbg("???DataFlash SPI master failed to enable gpio module\n");
		return false;
	}
	spi_status = spi_initMaster(AT45DBX_SPI, &spiOptions);
	if (SPI_OK != spi_status)
	{
		// Log the error details and return failure
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_MASTER_INIT_FAILED);
		print_dbg("???DataFlash SPI master failed to init\n");
		return false;
	}
	spi_status = spi_selectionMode(AT45DBX_SPI, 0, 0, 0);
	if (SPI_OK != spi_status)
	{
		// Log the error details and return failure
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_MASTER_MODE_FAILED);
		print_dbg("???DataFlash SPI master failed to select mode\n");
		return false;
	}
	df_status = df_init(spiOptions, sysclk_get_pba_hz());
	if (!df_status)
	{
		// Log the error details and return failure
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_INIT_FAILED);
		print_dbg("???DataFlash failed to init for SPI master\n");
		return false;
	}

	// Make it as an output
	//gpio_configure_pin(AVR32_SPI1_NPCS_1_PIN, GPIO_DIR_OUTPUT);
	//gpio_configure_pin(AT45DBX_SPI_SCK_PIN, GPIO_DIR_OUTPUT);

	// Enable SPI First.
	spi_enable(AT45DBX_SPI);
	return true;
}

/*! \brief Set to become SPI slave
 *  \retval True It is now SPI slave
 *  \retval False It failed to become SPI slave
 */
bool df_spi_slave (void)
{
	spi_status_t spi_status;

	// Disable SPI.
	spi_disable(AT45DBX_SPI);
	spi_status = spi_initSlave(AT45DBX_SPI, 8, 0);
	if (SPI_OK != spi_status)
	{
		// Log the error details and return failure
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_SLAVE_INIT_FAILED);
		print_dbg("???DataFlash SPI slave failed to init\n");
		return false;
	}

	// Enable SPI First.
	spi_enable(AT45DBX_SPI);
	// Make it as an input
	//gpio_configure_pin(AVR32_SPI1_NPCS_1_PIN, GPIO_DIR_INPUT);
	//gpio_configure_pin(AT45DBX_SPI_SCK_PIN, GPIO_DIR_INPUT);
	gpio_configure_pin(AT45DBX_SPI_MISO_PIN, GPIO_DIR_INPUT);
	return true;
}

/*! \brief Selects or unselects a DF memory.
 *
 * \param bSelect Boolean indicating whether the DF memory has to be selected (true) or unselected (false).
 */
void df_chipselect (bool bSelect)
{
  if (bSelect)
  {
    // Select SPI chip.
    spi_selectChip(AT45DBX_SPI, AT45DBX_SPI_NPCS);
  }
  else
  {
    // Unselect SPI chip.
    spi_unselectChip(AT45DBX_SPI, AT45DBX_SPI_NPCS);
  }
}

/*! \brief Waits until the DF is ready.
 *  \retval DF error code
 */
df_error_code_t df_wait_ready (void)
{
  U16 status;
  spi_status_t spi_status;
  df_error_code_t df_status = DF_RW_SUCCESS;

  // Select the DF.
  df_chipselect(true);

  // Send the Status Register Read command.
  spi_status = spi_write(AT45DBX_SPI, AT45DBX_CMDC_RD_STATUS_REG);
  if (spi_status != SPI_OK)
  {
    // Log the error details
    //NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
    //NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (AT45DBX_CMDC_RD_STATUS_REG << 16) | spi_status);
	df_status = DF_SPI_WRITE_FAILED;
  }

  if (DF_RW_SUCCESS == df_status)
  {
    // Read the status register until the DF is ready.
    do
    {
      // Send a dummy byte to read the status register.
      spi_status = spi_write_dummy();
      if (spi_status != SPI_OK)
      {
        // Log the error details
        //NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
        //NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (0xFF << 16) | spi_status); // dummy data is 0xFF
        df_status = DF_SPI_WRITE_FAILED;
	    break;
      }
      spi_status = spi_read(AT45DBX_SPI, &status);
      if (spi_status != SPI_OK)
      {
	      // Log the error details
	      //NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_READ_FAILED);
	      //NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (AT45DBX_CMDC_RD_STATUS_REG << 16) | spi_status);
	      df_status = DF_SPI_READ_FAILED;
	      break;
      }
    } while ((status & AT45DBX_MSK_BUSY) == AT45DBX_BUSY);
  }

  // Unselect the DF.
  df_chipselect(false);
  
  return df_status;
}

/*! \brief Read DF ID.
 * \param[inout] id Pointer to DF ID structure
 * \retval True DF ID is read
 * \retval False DFID cannot be read
 */
static bool df_read_id (df_id_t *id)
{
  U16 data;
  df_error_code_t df_status;
  spi_status_t spi_status;

  if (!df_spi_master())
  {
	  return false;
  }
  
  // Wait until DataFlash is ready.
  df_status = df_wait_ready();
  if (DF_RW_SUCCESS != df_status)
  {
    // Log the error details
    //NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_WAIT_READY_FAILED);
    //NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, df_status);
    return false;
  }
	
  // Select the DF.
  df_chipselect(true);

  // Send the Status Register Read command.
  spi_status = spi_write(AT45DBX_SPI, AT45DBX_CMDC_RD_MNFCT_DEV_ID_SM);
  if (SPI_OK == spi_status)
  {
    // Send series of dummy bytes to read DF manufacturer and device IDs.
    spi_write_dummy();
    spi_read(AT45DBX_SPI, &data);
    id->manufacturer_id = data;

    spi_write_dummy();
    spi_read(AT45DBX_SPI, &data);
    id->device_id_1 = data;

    spi_write_dummy();
    spi_read(AT45DBX_SPI, &data);
    id->device_id_2 = data;

    spi_write_dummy();
    spi_read(AT45DBX_SPI, &data);
    id->ext_info_len = data;
  }
  else
  {
    // Log the error details
    //NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
    //NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (AT45DBX_CMDC_RD_MNFCT_DEV_ID_SM << 16) | spi_status);
  }

  // Unselect the DF.
  df_chipselect(false);

  if (!df_spi_slave())
  {
	  return false;
  }
  return true;
}

/*! \brief Initializes AT45DBX DataFlash resources: GPIO, SPI and AT45DBX.
 */
void df_interface_init(void)
{
  // Assign I/Os to SPI.
  gpio_enable_module(AT45DBX_SPI_GPIO_MAP,
                     sizeof(AT45DBX_SPI_GPIO_MAP) / sizeof(AT45DBX_SPI_GPIO_MAP[0]));
}

/*! \brief Read and display AT45DBX DataFlash ID
 */
void df_display_id (void)
{
  // DF IDs
  df_id_t dfID;
  
  // Show DataFlash hardware ID
  if (df_read_id(&dfID))
  {
	print_debug_append("DF ID:%02X-%02X-%02X-%02X\r\n", dfID.manufacturer_id, dfID.device_id_1, dfID.device_id_2, dfID.ext_info_len);
  }
  else
  {
    //NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_READ_ID_FAILED);
	print_dbg("???Failed to read DF ID\r\n");
  }
}

/**
 * \brief Verify given DataFlash page by reading and comparing with the source data
 * \param[in] df_page_num DF Page number to verify
 * \param[in] data_source Source of data to compare with
 * \param[in] size_to_verify Amount of data to verify; should be up to the page size
 * \return DF error
 * \retval DF_RW_SUCCESS - Page is the same as the source data
 * \retval DF_BUFFER_OUT_OF_MEMORY - No more memory to allocate a buffer
 * \retval DF_READ_AFTER_WRITE_VERIFICATION_FAILED - Failed to verify the page contents in DataFlash
 */
static df_error_code_t df_verify_page (uint16_t df_page_num, uint8_t *data_source, uint16_t size_to_verify)
{
	df_error_code_t df_status = DF_RW_SUCCESS;
	uint8_t *temp_buff;
	
	temp_buff = malloc(size_to_verify);
	if (NULL == temp_buff)
	{
		df_status = DF_BUFFER_OUT_OF_MEMORY;
	}
	else
	{
		df_status = df_read_page(df_page_num, temp_buff, size_to_verify);
	}
	if (DF_RW_SUCCESS == df_status)
	{
		// Compare source data and data read from DataFlash page
		for (int i = 0; i < size_to_verify; i++)
		{
			if (data_source[i] != temp_buff[i])
			{
				df_status = DF_READ_AFTER_WRITE_VERIFICATION_FAILED;
				break;
			}
		}
	}
	if (NULL != temp_buff)
	{
		free(temp_buff);
	}
	return df_status;
}

/**
 * \brief Prepare to read from the given page in DataFlash
 * param[in] df_page_addr DataFlash page address in multiple of 2048 bytes
 * \return DF error 
 * \retval DF_RW_SUCCESS - DataFlash page is ready to read.
 */
df_error_code_t df_read_open (uint32_t df_page_addr)
{
	df_error_code_t df_status = DF_RW_SUCCESS;
	spi_status_t spi_status;

	// Do not allow to read another page if DF is already opened for reading
	if (df_is_opened)
	{
		return DF_READ_OPEN_FAILED;
	}
	else
	{
		df_is_opened= true;
	}
	
	if (!df_spi_master())
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_MASTER_FAILED);
		return DF_SPI_MASTER_FAILED;
	}
  
	// Wait until DataFlash is ready.
	df_status = df_wait_ready();
	if (DF_RW_SUCCESS != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_WAIT_READY_FAILED);
		return DF_WAIT_READY_FAILED;
	}
	
	// Select the DataFlash.
	df_chipselect(true);

	// Send the Main Memory Page Read command.
	spi_status = spi_write(AT45DBX_SPI, AT45DBX_CMDA_RD_PAGE);
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (AT45DBX_CMDA_RD_PAGE << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}

	// Send the three address bytes
	spi_status = spi_write(AT45DBX_SPI, LSB2W(df_page_addr));
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (LSB2W(df_page_addr) << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}
	spi_status = spi_write(AT45DBX_SPI, LSB1W(df_page_addr));
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (LSB1W(df_page_addr) << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}
	spi_status = spi_write(AT45DBX_SPI, LSB0W(df_page_addr));
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (LSB0W(df_page_addr) << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}

	// Send 32 don't care clock cycles to initialize the read operation.
	spi_status = spi_write_dummy();
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (0xFF << 16) | spi_status); // dummy data is oxFF
		return DF_SPI_WRITE_FAILED;
	}
	spi_status = spi_write_dummy();
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (0xFF << 16) | spi_status); // dummy data is oxFF
		return DF_SPI_WRITE_FAILED;
	}
	spi_status = spi_write_dummy();
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (0xFF << 16) | spi_status); // dummy data is oxFF
		return DF_SPI_WRITE_FAILED;
	}
	spi_status = spi_write_dummy();
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (0xFF << 16) | spi_status); // dummy data is oxFF
		return DF_SPI_WRITE_FAILED;
	}

	return DF_RW_SUCCESS;
}

/**
 * \brief Prepare to open the given page in DataFlash
 * param[in] df_page_addr DF page address in multiple of 2048 bytes
 * \return DF error
 * \retval DF_RW_SUCCESS - DataFlash page is ready to be written.
 */
df_error_code_t df_write_open (uint32_t df_page_addr)
{
	df_error_code_t df_status;
	spi_status_t spi_status;

	// Check and stop opening DF again
	if (df_is_opened)
	{
		return DF_WRITE_OPEN_FAILED;
	}
	else
	{
		df_is_opened= true;
	}
	
	if (!df_spi_master())
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_MASTER_FAILED);
		return DF_SPI_MASTER_FAILED;
	}
  
  	// Wait until DataFlash is ready.
	df_status = df_wait_ready();
	if (DF_RW_SUCCESS != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_WAIT_READY_FAILED);
		return DF_WAIT_READY_FAILED;
	}
	
	// Select the DataFlash.
	df_chipselect(true);

	// Transfer the content of the current page to buffer 1.
	// Send the Main Memory Page to Buffer 1 Transfer command.
	spi_status = spi_write(AT45DBX_SPI, AT45DBX_CMDB_XFR_PAGE_TO_BUF1);
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (AT45DBX_CMDB_XFR_PAGE_TO_BUF1 << 16) | spi_status); // dummy data is oxFF
		return DF_SPI_WRITE_FAILED;
	}

	// Send the three address bytes
	spi_status = spi_write(AT45DBX_SPI, LSB2W(df_page_addr));
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (LSB2W(df_page_addr) << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}
	spi_status = spi_write(AT45DBX_SPI, LSB1W(df_page_addr));
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (LSB1W(df_page_addr) << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}
	spi_status = spi_write(AT45DBX_SPI, LSB0W(df_page_addr));
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (LSB0W(df_page_addr) << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}

	// Unselect the DF memory.
	df_chipselect(false);

	// Wait for end of page transfer.
	df_status = df_wait_ready();
	if (DF_RW_SUCCESS != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_WAIT_READY_FAILED);
		return DF_WAIT_READY_FAILED;
	}

	// Select the DataFlash again.
	df_chipselect(true);

	// Send the Main Memory Page Program through Buffer 1 command.
	spi_status = spi_write(AT45DBX_SPI, AT45DBX_CMDB_PR_PAGE_TH_BUF1);
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (AT45DBX_CMDB_PR_PAGE_TH_BUF1 << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}

	// Send the three address bytes
	spi_status = spi_write(AT45DBX_SPI, LSB2W(df_page_addr));
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (LSB2W(df_page_addr) << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}
	spi_status = spi_write(AT45DBX_SPI, LSB1W(df_page_addr));
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (LSB1W(df_page_addr) << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}
	spi_status = spi_write(AT45DBX_SPI, LSB0W(df_page_addr));
	if (SPI_OK != spi_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_WRITE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (LSB0W(df_page_addr) << 16) | spi_status);
		return DF_SPI_WRITE_FAILED;
	}
	
	return DF_RW_SUCCESS;
}

/**
 * \brief Close the DataFlash
 * \return DF error
 * \retval DF_RW_SUCCESS - DataFlash is unselected.
 */
df_error_code_t df_close (void)
{
	// Unselect the DataFlash.
	df_chipselect(false);
	
	if (!df_spi_slave())
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_SLAVE_FAILED);
		return DF_CLOSE_FAILED;
	}
	// DF is now closed
	df_is_opened = false;
	return DF_RW_SUCCESS;
}

/**
 * \brief Read data from given DataFlash page 
 * \param[in] df_page_num DF Page number to read from
 * \param[in] data_dest Destination of data read from DataFlash
 * \param[in] size_to_read Amount of data to read; should be up to the page size
 * \return DF error
 * \retval DF_RW_SUCCESS - Page is read successfully.
 * \retval DF_READING_TOO_MANY_DATA - Page size is too big
 */
df_error_code_t df_read_page (uint16_t df_page_num, uint8_t *data_dest, uint16_t size_to_read)
{
	df_error_code_t df_status;
	uint16_t i;
	uint16_t data;
	uint32_t df_page_addr;
	spi_status_t spi_status;

	if (size_to_read > DF_PAGE_SIZE)
	{
		return DF_READING_TOO_MANY_DATA;
	}
	
	// Convert page number to page address in multiple of internal DataFlash page steps
	df_page_addr = df_page_num * DF_PAGE_STEP;
	
	// Access the DataFlash to prepare to read the page
	df_status = df_read_open(df_page_addr);
	if (DF_RW_SUCCESS != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_READ_OPEN_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (df_page_num << 16) | df_status);
	}
	else
	{
		// Read the DataFlash page.
		for (i = 0; i < size_to_read; i++)
		{
			// Send a dummy byte to read the next data byte. Do not increment the given data destination here.
			// Let the caller to adjust it if this function is called multiple times to read multiple pages.
			spi_status = spi_write_dummy();
			if (spi_status != SPI_OK)
			{
				df_status = DF_SPI_WRITE_FAILED;
				break;
			}
			spi_status = spi_read(AT45DBX_SPI, &data);
			if (spi_status != SPI_OK)
			{
				df_status = DF_SPI_READ_FAILED;
				break;
			}
			*(data_dest + i) = data;
		}
	}
	// Release access to the DataFlash.
	if (DF_RW_SUCCESS == df_status)
	{
		print_dbg("r");
		df_status = df_close();
	}
	else if (DF_READ_OPEN_FAILED != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_READ_PAGE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (df_page_num << 16) | df_status);
		print_debug_append("???r%d\n", df_page_num);
		
		// Ignore the close status if there's already a failure
		df_close();
	}
	return df_status;
}

/**
 * \brief Read data from multiple DataFlash pages starting from the given page
 * \param[in] df_page_num Starting DataFlash page number to read from
 * \param[in] data_dest Destination of data read from DataFlash
 * \param[in] size_to_read Amount of data to read; could be more than a page
 * \return DF error
 * \retval DF_RW_SUCCESS - Page is read successfully.
 * \retval DF_READING_TOO_MANY_DATA - Page size is too big
 */
df_error_code_t df_read_multiple_pages (uint16_t df_page_num, uint8_t *data_dest, uint16_t size_to_read)
{
	df_error_code_t df_status = DF_RW_SUCCESS;
	
	// Read one page at a time from DataFlash into given destination
	while ((DF_RW_SUCCESS == df_status) && (size_to_read >= DF_PAGE_SIZE))
	{
		df_status = df_read_page(df_page_num, data_dest, DF_PAGE_SIZE);

		// Prepare to write to next page
		df_page_num++;
		data_dest += DF_PAGE_SIZE;
		size_to_read -= DF_PAGE_SIZE;
	}
	// Write the remaining bytes from given source to DataFlash
	if ((DF_RW_SUCCESS == df_status) && (size_to_read > 0))
	{
		df_status = df_read_page(df_page_num, data_dest, size_to_read);
		// Advance to next page which is re-adjusted when logging error details
		df_page_num++;
	}
	if (DF_RW_SUCCESS != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_READ_MULTI_PAGE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, df_status);
		print_debug_append("???Reading multiple pages to DataFlash failed; error %d\n", df_status);
	}
	return df_status;
}

/**
 * \brief Write data to DataFlash now at the given page
 * \note If data to write is less than the page size, remaining bytes are zero filled.
 * \param[in] df_page_number DataFlash page number to write to
 * \param[in] data_source Source of data to program into DataFlash
 * \param[in] size_to_write Amount of data to write; should be up to the page size
 * \return DF error
 * \retval DF_RW_SUCCESS - Page is written successfully.
 * \retval DF_WRITING_TOO_MANY_DATA - Page size is too big
 */
static df_error_code_t df_write_page_now (uint16_t df_page_num, uint8_t *data_source, uint16_t size_to_write)
{
	df_error_code_t df_status = DF_RW_SUCCESS;
	uint16_t i;
	spi_status_t spi_status;
	uint32_t df_page_addr;

	// Convert page number to page address in multiple of internal DataFlash page steps
	df_page_addr = df_page_num * DF_PAGE_STEP;
	
	// Access the DataFlash to prepare to program the page
	df_status = df_write_open(df_page_addr);
	if (DF_RW_SUCCESS != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_WRITE_OPEN_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (df_page_num << 16) | df_status);
	}
	else
	{
		// Program the page.
		for (i = 0; i < size_to_write; i++)
		{
			// Write the next data byte. Do not increment the given data source here.
			// Let the caller to adjust it if this function is called multiple times to write multiple pages.
			spi_status = spi_write(AT45DBX_SPI, *(data_source + i));
			if (spi_status != SPI_OK)
			{
				df_status = DF_SPI_WRITE_FAILED;
				break;
			}
		}
		// If the end of page is not reached, fill the remaining page bytes.
		if (DF_RW_SUCCESS == df_status && size_to_write < DF_PAGE_SIZE)
		{
			for (i = DF_PAGE_SIZE - size_to_write; i; i--)
			{
				spi_status = spi_write(AT45DBX_SPI, 0x55);
				if (spi_status != SPI_OK)
				{
					df_status = DF_SPI_WRITE_FAILED;
					break;
				}
			}
		}
	}
	// Release access to the DataFlash.
	if (DF_RW_SUCCESS == df_status)
	{
		print_debug_append("w", df_page_num);
		df_status = df_close();
	}
	else
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_WRITE_PAGE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, (df_page_num << 16) | df_status);
		print_debug_append("???w%d\n", df_page_num);
		
		// Ignore the close status if there's already a failure
		df_close();
	}
	return df_status;
}

/**
 * \brief Write data to DataFlash at the given page
 * \param[in] df_page_number DataFlash page number to write to
 * \param[in] data_source Source of data to program into DataFlash
 * \param[in] size_to_write Amount of data to write; should be up to the page size
 * \return DF error
 * \retval DF_RW_SUCCESS - Page is written successfully.
 * \retval DF_WRITING_TOO_MANY_DATA - Page size is too big
 */
df_error_code_t df_write_page (uint16_t df_page_num, uint8_t *data_source, uint16_t size_to_write)
{
	df_error_code_t df_status = DF_RW_SUCCESS;
	df_write_page_node *next_node;

	if (size_to_write > DF_PAGE_SIZE)
	{
		return DF_WRITING_TOO_MANY_DATA;
	}
	
	// Serialise to write the given DF page in case the foreground task was interrupted in the middle of writing to a DF page
	next_node = malloc(sizeof(df_write_page_node));
	if (NULL == next_node)
	{
		// No more memory for new node
		print_dbg("No more memory left to allocate a new node to serialise DF write page\r\n");
		return DF_WRITE_PAGE_NODE_FAILED;
	}
	else
	{
		next_node->page_number = df_page_num;
		next_node->data_size = size_to_write;
		next_node->next = NULL;
		next_node->data_copy = malloc(size_to_write);
		if (next_node->data_copy == NULL)
		{
			// No more memory to keep a copy of DF write page
			print_dbg("No more memory left to keep a copy of DF write page\r\n");
			free(next_node);
			return DF_WRITE_PAGE_COPY_FAILED;
		}
		memcpy(next_node->data_copy, data_source, size_to_write);
	}
	// Keep the DF page to write in the queue first
	enque_df_write_page(next_node);

	// Postpone to write the DF page if DF is currently opened
	if (df_is_opened)
	{
		print_dbg(">W<");
		df_status = DF_RW_SUCCESS;
	}
	else
	{
		// While there is a DF page in the queue, write it to DF now 
		while (next_node = deque_df_write_page())
		{
			df_status = df_write_page_now(next_node->page_number, next_node->data_copy, next_node->data_size);
			if (DF_RW_SUCCESS != df_status)
			{
				// Failed to write the DF page which was postponed
				print_debug_append("Failed to write delayed DF page=%d size=%d\r\n", next_node->page_number, next_node->data_size);
			}
			free(next_node->data_copy);
			free(next_node);
		}
	}
	return df_status;
}

/**
 * \brief Write data to DataFlash consecutively starting from the given page
 * \note If data to write is less than the page size, remaining bytes are zero filled.
 * \param[in] df_page_num DataFlash page number to start writing to
 * \param[in] data_source Source of data to program into DataFlash
 * \param[in] size_to_write Amount of data to write; could be more than a page
 * \return DF error
 * \retval DF_RW_SUCCESS - Page is written successfully.
 * \retval DF_WRITING_TOO_MANY_DATA - Page size is too big
 */
df_error_code_t df_write_multiple_pages (uint16_t df_page_num, uint8_t *data_source, uint16_t size_to_write)
{
	df_error_code_t df_status = DF_RW_SUCCESS;

	// Write one page at a time, from given source to DataFlash
	while ((DF_RW_SUCCESS == df_status) && (size_to_write >= DF_PAGE_SIZE))
	{
		df_status = df_write_page(df_page_num, data_source, DF_PAGE_SIZE);
		
		// Verify the page just written
		if (DF_RW_SUCCESS == df_status)
		{
			df_status = df_verify_page(df_page_num, data_source, DF_PAGE_SIZE);
		}
		// Prepare to write to next page
		df_page_num++;
		data_source += DF_PAGE_SIZE;
		size_to_write -= DF_PAGE_SIZE;
	}
	// Write the remaining bytes from given source to DataFlash
	if ((DF_RW_SUCCESS == df_status) && (size_to_write > 0))
	{
		df_status = df_write_page(df_page_num, data_source, size_to_write);

		// Verify the page just written
		if (DF_RW_SUCCESS == df_status)
		{
			df_status = df_verify_page(df_page_num, data_source, size_to_write);
		}
		// Advance to next page which is re-adjusted when logging error details
		df_page_num++;
	}
	if (DF_RW_SUCCESS != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_WRITE_MULTI_PAGE_FAILED);
		//NOT PORTED YET print_debug(LOG_TYPE_32BIT_COMMON_DATA, df_status);
		print_debug_append("???Writing multiple pages to DataFlash failed; error %d\n", df_status);
	}
	return df_status;
}

/**
 * \brief Erase the given page in DataFlash
 * \param[in] page_num DF page number
 * \return DF error
 * \retval DF_RW_SUCCESS - page erased command is sent.
 */
df_error_code_t df_erase_page (uint16_t page_num)
{
	df_error_code_t df_status;
	uint32_t addr = page_num * DF_PAGE_STEP;
	
	//print_debug_append("Erasing DF page %d\n", page_num);
	print_dbg("x");
	
	if (!df_spi_master())
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_MASTER_FAILED);
		return DF_SPI_MASTER_FAILED;
	}
	
	// Wait until DataFlash is ready.
	df_status = df_wait_ready();
	if (DF_RW_SUCCESS != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_WAIT_READY_FAILED);
		return DF_WAIT_READY_FAILED;
	}
	
	// Select the DataFlash.
	df_chipselect(true);

	// Send the Erase Page command.
	spi_write(AT45DBX_SPI, AT45DBX_CMDB_ER_PAGE);

	// Send the three address bytes
	spi_write(AT45DBX_SPI, LSB2W(addr));
	spi_write(AT45DBX_SPI, LSB1W(addr));
	spi_write(AT45DBX_SPI, LSB0W(addr));
	
	// Wait until DataFlash is ready.
	df_status = df_wait_ready();
	if (DF_RW_SUCCESS != df_status)
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_WAIT_READY_FAILED);
		return DF_WAIT_READY_FAILED;
	}
	
	// Unselect the DataFlash to erase the page
	df_chipselect(false);

	if (!df_spi_slave())
	{
		// Log the error details
		//NOT PORTED YET print_debug(LOG_TYPE_CBP_ERROR, DF_SPI_SLAVE_FAILED);
		return DF_SPI_SLAVE_FAILED;
	}

	return DF_RW_SUCCESS;
}

