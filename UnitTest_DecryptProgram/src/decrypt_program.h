/**
 * \file
 *
 * \brief Encrypt/Decrypt CBP image.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 4/04/2014 4:08:35 PM
 * \author yoonl
 */


#ifndef DECRYPT_PROGRAM_H_
#define DECRYPT_PROGRAM_H_

#include <asf.h>

void general_setup(const struct test_case *test);
void general_cleanup(const struct test_case *test);
void run_CheckCbpBinaryImage_test(const struct test_case *test);
void run_ProgramAndVerifyMCU_test(const struct test_case *test);
void run_EraseMcuFlash_test(const struct test_case *test);
void run_WriteToMcuFlash_test(const struct test_case *test);
void run_CheckMcuFlash_test(const struct test_case *test);

DEFINE_TEST_CASE(CheckCbpBinaryImage_test, NULL, run_CheckCbpBinaryImage_test, general_cleanup, "Check CBP binary image test");
DEFINE_TEST_CASE(ProgramAndVerifyMCU_test, NULL, run_ProgramAndVerifyMCU_test, general_cleanup, "Program and verify CBP binary image test");
DEFINE_TEST_CASE(EraseMcuFlash_test, NULL, run_EraseMcuFlash_test, NULL, "Erase MCU Flash test");
DEFINE_TEST_CASE(WriteToMcuFlash_test, NULL, run_WriteToMcuFlash_test, NULL, "Write MCU Flash test");
DEFINE_TEST_CASE(CheckMcuFlash_test, NULL, run_CheckMcuFlash_test, general_cleanup, "Check MCU Flash test");


#endif /* DECRYPT_PROGRAM_H_ */