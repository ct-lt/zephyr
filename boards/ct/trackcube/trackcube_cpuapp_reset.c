/*
* Cognid NORA-B10 board configuration
*/

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#define I2C_PULLUP_PIN_INIT_PRORITY 41

/* Check Initialization order:
1. GPIO
2. I2C Pullup Pin
3. Port Expander
4. Flash Power pin (which is controlled by the port expander by GPIO hog)
5. Flash
*/
BUILD_ASSERT(I2C_PULLUP_PIN_INIT_PRORITY > CONFIG_GPIO_INIT_PRIORITY);
#ifdef CONFIG_GPIO_PCA_SERIES_INIT_PRIORITY
#define PORT_EXPANDER_INIT_PRIO CONFIG_GPIO_PCA_SERIES_INIT_PRIORITY
#elif CONFIG_GPIO_PCAL6524_OOT_INIT_PRIORITY
#define PORT_EXPANDER_INIT_PRIO CONFIG_GPIO_PCAL6524_OOT_INIT_PRIORITY
#endif
BUILD_ASSERT(PORT_EXPANDER_INIT_PRIO > I2C_PULLUP_PIN_INIT_PRORITY);
BUILD_ASSERT(CONFIG_GPIO_HOGS_INIT_PRIORITY > PORT_EXPANDER_INIT_PRIO);
#ifdef CONFIG_NORDIC_QSPI_NOR_INIT_PRIORITY
// As long as gpio-hog is used for flash power
BUILD_ASSERT(CONFIG_NORDIC_QSPI_NOR_INIT_PRIORITY > CONFIG_GPIO_HOGS_INIT_PRIORITY);
#endif

LOG_MODULE_REGISTER(trackcube_nrf5340_cpuapp, CONFIG_LOG_DEFAULT_LEVEL);

static const struct gpio_dt_spec i2c_pullup_pin = GPIO_DT_SPEC_GET(DT_NODELABEL(i2c_pullup), gpios);

static int set_pullup_pin(void)
{
	if (!gpio_is_ready_dt(&i2c_pullup_pin)) {
		LOG_ERR("GPIO not ready");
		return 0;
	}
	int ret = gpio_pin_configure_dt(&i2c_pullup_pin, GPIO_OUTPUT_ACTIVE);
	if (ret != 0) {
		LOG_ERR("Failed to configure GPIO");
	}
	k_msleep(100);

	return ret;
}

SYS_INIT(set_pullup_pin, POST_KERNEL, I2C_PULLUP_PIN_INIT_PRORITY);