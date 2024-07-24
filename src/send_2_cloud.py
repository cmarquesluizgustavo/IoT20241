import pandas as pd
import requests
import time
import logging
from typing import Optional

# Set up logging
logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s"
)


def check_connectivity(url: str = "http://www.google.com", timeout: int = 5) -> bool:
    """
    Check internet connectivity.

    Args:
        url (str): URL to check connectivity.
        timeout (int): Timeout for the request.

    Returns:
        bool: True if connected, False otherwise.
    """
    try:
        requests.get(url, timeout=timeout)
        return True
    except requests.RequestException:
        return False


def send_data_to_sql(data: pd.DataFrame, url: str) -> bool:
    """
    Send the data to the SQL endpoint.

    Args:
        data (pd.DataFrame): Data to be sent.
        url (str): Endpoint URL.

    Returns:
        bool: True if data was sent successfully, False otherwise.
    """
    try:
        data.to_sql("sensor_data", url)
        return True
    except Exception as e:
        logging.error(f"Failed to send data: {e}")
        return False


def read_csv(file_path: str) -> pd.DataFrame:
    """
    Read the CSV file.

    Args:
        file_path (str): Path to the CSV file.

    Returns:
        pd.DataFrame: Data read from the CSV file.
    """
    try:
        data = pd.read_csv(file_path)
        return data
    except Exception as e:
        logging.error(f"Failed to read CSV file: {e}")
        return None


def main(file_path: str, endpoint_url: str, check_interval: int = 120):
    """
    Main function to check connectivity, read CSV, and send data.

    Args:
        file_path (str): Path to the CSV file.
        endpoint_url (str): Endpoint URL to send data.
        check_interval (int): Interval to check connectivity in seconds (default: 120).
    """
    while True:
        already_sent = False
        if check_connectivity():
            if not already_sent:
                logging.info("Internet connection available and data not sent yet.")
                data = read_csv(file_path)
                if data is None:
                    logging.error("Failed to read data.")
                else:
                    if send_data_to_sql(data, endpoint_url):
                        already_sent = True
                        logging.info("Data sent successfully.")
                    else:
                        logging.error("Failed to send data.")
        else:
            already_sent = False
        time.sleep(check_interval)


if __name__ == "__main__":
    FILE_PATH = "/sensor_data.csv"
    ENDPOINT_URL = "http://cloud_mock_url.com:12345"
    main(FILE_PATH, ENDPOINT_URL)
