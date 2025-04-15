# Cognid NORA-B10 board configuration

# Copyright (c) 2023 u-blox AG
# SPDX-License-Identifier: Apache-2.0

if (CONFIG_BOARD_TRACKCUBE_NRF5340_CPUAPP OR CONFIG_BOARD_TRACKCUBE_NRF5340_CPUAPP_NS)
    zephyr_library()
    zephyr_library_sources(trackcube_cpuapp_reset.c)
    if (CONFIG_BOARD_ENABLE_CPUNET)
        zephyr_library_sources(trackcube_cpunet_reset.c)

        if (CONFIG_BUILD_WITH_TFM)
            zephyr_library_include_directories(
                    $<TARGET_PROPERTY:tfm,TFM_BINARY_DIR>/api_ns/interface/include
            )
        endif ()

    endif ()
endif ()