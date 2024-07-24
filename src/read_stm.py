import time
import spidev
import pandas as pd
import logging
from typing import List, Dict, Any

# Setup logging
logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s"
)
logger = logging.getLogger(__name__)


def init_spi(
    bus: int, device: int, speed: int = 500000, mode: int = 0
) -> spidev.SpiDev:
    """
    Initialize SPI connection.

    Args:
        bus (int): SPI bus number.
        device (int): SPI device number.
        speed (int): SPI speed in Hz. Default is 500000.
        mode (int): SPI mode. Default is 0.

    Returns:
        spidev.SpiDev: Configured SPI device.
    """
    spi = spidev.SpiDev()
    spi.open(bus, device)
    spi.max_speed_hz = speed
    spi.mode = mode
    logger.info(
        f"Initialized SPI on bus {bus}, device {device}, speed {speed}Hz, mode {mode}."
    )
    return spi


def read_sensor_data(spi: spidev.SpiDev) -> Dict[str, Any]:
    """
    Read sensor data from the SPI device.

    Args:
        spi (spidev.SpiDev): The SPI device.

    Returns:
        Dict[str, Any]: A dictionary containing sensor name and value.
    """
    # JUST A PLACE HOLDER
    # WE COULDN'T TEST HOW THE COMMUNICATION COMES THROUGH SPI
    msg = [0x77]  # Example message
    result = spi.xfer2(msg)
    sensor_data = {"ts": time.time(), "sensorName": "ExampleSensor", "value": result[0]}
    logger.info(f"Read sensor data: {sensor_data}")
    return sensor_data


def main() -> None:
    """
    Main function to initialize SPI, collect sensor data in an endless loop, and save it to a CSV file.
    """
    bus = 0
    device = 1

    spi = init_spi(bus, device)
    csv_file = "/sensor_data.csv"

    try:
        while True:
            sensor_data = read_sensor_data(spi)
            df = pd.DataFrame([sensor_data])

            # Append to CSV file
            df.to_csv(
                csv_file,
                mode="a",
                header=not pd.io.common.file_exists(csv_file),
                index=False,
            )
            logger.info("Appended sensor data to sensor_data.csv.")

            time.sleep(0.1)

    except KeyboardInterrupt:
        logger.info("Data collection interrupted by user.")
    finally:
        spi.close()
        logger.info("SPI connection closed.")


if __name__ == "__main__":
    main()
