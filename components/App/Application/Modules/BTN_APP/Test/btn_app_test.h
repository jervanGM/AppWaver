#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

/**
 * @brief Test for checking major faults in the button application.
 *
 * This test verifies the button application's behavior when major faults are detected.
 * It initializes error slots with specific values and checks the expected fault status.
 */
void test_btn_app_check_mayor_faults(); /**< \test */

/**
 * @brief Test for checking minor faults in the button application.
 *
 * This test verifies the button application's behavior when minor faults are detected.
 * It initializes error slots with specific values and checks the expected fault status.
 */
void test_btn_app_check_minor_faults(); /**< \test */

/**
 * @brief Test for checking no faults in the button application.
 *
 * This test verifies the button application's behavior when no faults are detected.
 * It initializes error slots with specific values and checks the expected fault status.
 */
void test_btn_app_check_no_faults(); /**< \test */

/**
 * @brief Test for checking lower minor fault boundary in the button application.
 *
 * This test verifies the button application's behavior near the lower boundary of minor faults.
 * It initializes error slots with specific values and checks the expected fault status.
 */
void test_btn_app_check_lower_minor_fault_boundary(); /**< \test */

/**
 * @brief Test for checking upper minor fault boundary in the button application.
 *
 * This test verifies the button application's behavior near the upper boundary of minor faults.
 * It initializes error slots with specific values and checks the expected fault status.
 */
void test_btn_app_check_upper_minor_fault_boundary(); /**< \test */

/**
 * @brief Test for checking lower major fault boundary in the button application.
 *
 * This test verifies the button application's behavior near the lower boundary of major faults.
 * It initializes error slots with specific values and checks the expected fault status.
 */
void test_btn_app_check_lower_major_fault_boundary(); /**< \test */

/**
 * @brief Test for checking upper major fault boundary in the button application.
 *
 * This test verifies the button application's behavior near the upper boundary of major faults.
 * It initializes error slots with specific values and checks the expected fault status.
 */
void test_btn_app_check_upper_major_fault_boundary(); /**< \test */

/**
 * @brief Test for processing short press command in the button application.
 *
 * This test verifies the button application's behavior when processing a short press command.
 * It initializes the pulse type and checks the expected command after processing.
 */
void test_btn_app_process_short_press_cmd(); /**< \test */

/**
 * @brief Test for processing long press command in the button application.
 *
 * This test verifies the button application's behavior when processing a long press command.
 * It initializes the pulse type and checks the expected command after processing.
 */
void test_btn_app_process_long_press_cmd(); /**< \test */

/**
 * @brief Test for processing power off command in the button application.
 *
 * This test verifies the button application's behavior when processing a power off command.
 * It initializes the pulse type and checks the expected command after processing.
 */
void test_btn_app_process_power_off_cmd(); /**< \test */

/**
 * @brief Test for processing no pulse command in the button application.
 *
 * This test verifies the button application's behavior when processing a no pulse command.
 * It initializes the pulse type and checks the expected command after processing.
 */
void test_btn_app_process_no_pulse_cmd(); /**< \test */

/**
 * @brief Test for processing error command in the button application.
 *
 * This test verifies the button application's behavior when processing an error command.
 * It initializes the pulse type and checks the expected command after processing.
 */
void test_btn_app_process_error_cmd(); /**< \test */

/**
 * @brief Test for processing unknown command in the button application.
 *
 * This test verifies the button application's behavior when processing an unknown command.
 * It initializes the pulse type and checks the expected command after processing.
 */
void test_btn_app_process_unknown_cmd(); /**< \test */

/**
 * @brief Test for combination of short and long press commands in the button application.
 *
 * This test verifies the button application's behavior when processing a sequence of short and long press commands.
 * It initializes the pulse types in different sequences and checks the expected commands after processing each pulse.
 */
void test_short_and_long_press_combination(); /**< \test */

/**
 * @brief Test for processing short press after long press command in the button application.
 *
 * This test verifies the button application's behavior when processing a short press command immediately after a long press.
 * It initializes the pulse types and checks the expected commands after processing each pulse.
 */
void test_short_press_after_long_press(); /**< \test */

#endif /* TRACE_TEST_H_ */
