# ESP32-C3-Telegram-Power-On-Notification

# ESP32-C3 Telegram Power-On Notification

This project uses an ESP32-C3 microcontroller to send a Telegram message to multiple chat IDs when the device powers on and connects to Wi-Fi. It also activates a buzzer for 5 seconds to signal power-on. The project is designed for IoT applications, such as remote startup notifications.

## Features
- Sends a Telegram message to 5 predefined chat IDs when the ESP32-C3 powers on and connects to Wi-Fi.
- Activates a buzzer connected to GPIO 18 for 5 seconds on startup.
- Uses RTC memory to ensure messages are sent only once per power cycle, even if the device resets.
- Disables brownout detector to prevent resets due to power instability (temporary workaround).

## Hardware Requirements
- **ESP32-C3 Development Board** (e.g., ESP32-C3-DevKitM-1)
- **Active Buzzer** connected to GPIO 18
- **Stable Power Supply** (5V USB or 3.3V external, 500mA+ recommended)
- **Optional**: 10µF–100µF capacitor across VCC and GND to stabilize power
- **Wi-Fi Router** with internet access

## Software Requirements
- **Arduino IDE** or **PlatformIO** with ESP32-C3 support
- **Libraries**:
  - WiFi.h` (included with ESP32 Arduino core)
  - HTTPClient.h` (included with ESP32 Arduino core)
- **Telegram Bot**:
  - Create a bot using @BotFather` on Telegram to get a bot token.
  - Obtain chat IDs for the recipients (see **Creating a Telegram Bot and Obtaining Chat IDs** section).

## Circuit Diagram
VCC (3.3V) ----||----[10µF–100µF Capacitor]---- ESP32-C3 VCC
ESP32-C3 GPIO18 ----------------[Buzzer +]-------|
ESP32-C3 GND -------------------[Buzzer -]------- GND


**Notes**:
- The capacitor is optional but recommended to prevent brownout resets.
- Ensure the buzzer’s positive pin is connected to GPIO 18 and negative to GND.
- If the buzzer draws high current, use an NPN transistor (e.g., 2N2222) to drive it.

## Creating a Telegram Bot and Obtaining Chat IDs
To send Telegram messages, you need to create a bot and get the chat IDs of the recipients. Follow these steps:

1. **Create a Telegram Bot**:
   - Open Telegram and search for `@BotFather`.
   - Send `/start` to begin.
   - Send `/newbot` to create a new bot.
   - Follow the prompts to name your bot (e.g., MyESP32Bot) and set a username (e.g., @MyESP32Bot`).
   - `@BotFather` will provide a bot token (e.g., 8243146761:AAHdU1pmAI2oxFfFHDNmsFi`). Save this token securely.
   - Test the bot token by accessing `https://api.telegram.org/bot<your-bot-token>/getMe` in a browser. A valid token returns bot details; an invalid token returns an error.

2. **Obtain Chat IDs**:
   - Open Telegram and send a message (e.g., /start`) to your bot from each recipient’s account.
   - Access https://api.telegram.org/bot<your-bot-token>/getUpdates` in a browser.
   - Look for the `chat` object in the JSON response. The `id` field is the chat ID (e.g., `6259013308`).
   - Alternatively, message `@getidsbot` from each recipient’s account to get their chat ID.
   - Collect the chat IDs for all 5 recipients and update the `chatIDs` array in the code.

3. **Configure the Code**:
   - Update the `botToken` variable in `esp32c3_telegram_with_logging.ino` with your bot token.
   - Update the `chatIDs` array with the 5 chat IDs.

## Setup Instructions
1. **Hardware Setup**:
   - Connect the buzzer’s positive pin to GPIO 18 and negative to GND.
   - Power the ESP32-C3 via USB (5V) or a stable 3.3V supply (500mA+).
   - Add a 10µF–100µF capacitor across VCC and GND near the ESP32-C3 to stabilize power.

2. **Software Setup**:
   - Install the Arduino IDE and add ESP32-C3 support (see [ESP32 Arduino Core Installation](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)).
   - Copy the code from esp32c3_telegram_with_logging.ino` into your IDE.
   - Update the following in the code:
     - ssid: Your Wi-Fi network name (e.g., Tamim-wifi`).
     - password: Your Wi-Fi password (e.g., Tamims9047@`).
     - botToken: Your Telegram bot token (obtained from @BotFather`).
     - chatIDs: Array of Telegram chat IDs (e.g., 6259013308`, `2017577128`, etc.).
   - Verify GPIO 18 is correct for your buzzer; adjust if needed.

3. **Upload and Test**:
   - Upload the code to your ESP32-C3.
   - Open the Serial Monitor (115200 baud) to monitor Wi-Fi connection and message status.
   - On power-on, the ESP32-C3 connects to Wi-Fi, sends a Telegram message to each chat ID, and activates the buzzer for 5 seconds.

## Code Explanation
- **Wi-Fi Connection**: Connects to the specified Wi-Fi network and waits until connected.
- **Telegram Notification**: Sends a message (⚡ ESP32-C3 Power ON & Turn off Ganearator ✅`) to 5 chat IDs using the Telegram Bot API.
- **Buzzer Control**: Activates the buzzer on GPIO 18 for 5 seconds on startup.
- **Brownout Fix**: Disables the brownout detector to prevent resets due to power instability.
- **RTC Memory**: Uses `RTC_DATA_ATTR` to ensure messages are sent only once per power cycle.

## Troubleshooting
- **No Telegram Messages**:
  - Check Serial Monitor for errors (e.g., HTTP code not 200).
  - Verify bot token and chat IDs (test with https://api.telegram.org/bot<token>/getMe`).
  - Ensure Wi-Fi credentials are correct and the router is online.
- **Brownout Resets**:
  - Use a stable power supply (500mA+).
  - Add a capacitor (10µF–100µF) across VCC and GND (see circuit diagram).
  - Consider driving the buzzer with an NPN transistor to reduce GPIO current draw.
- **Buzzer Not Working**:
  - Confirm GPIO 18 is correct for your board.
  - Test the buzzer independently with a simple sketch.

## Usage
- Power on the ESP32-C3.
- The device connects to Wi-Fi, sends a Telegram message to the specified chat IDs, and activates the buzzer for 5 seconds.
- No further messages are sent until the device is fully powered off and on again.

## Future Improvements
- Add a timeout for Wi-Fi connection attempts.
- Re-enable brownout detector after stabilizing the power supply.
- Add a manual reset button to clear the RTC memory flag.
- Support dynamic chat ID updates via a web interface.

## License
This project is licensed under the MIT License. See the LICENSE` file for details.

## Acknowledgments
- Built using the ESP32 Arduino Core and Telegram Bot API.
- Thanks to the ESP32 community for resources and support.
