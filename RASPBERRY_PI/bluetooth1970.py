from bluepy.btle import Peripheral
import tkinter as tk
import threading

result_window = None
result_label = None

def create_result_window():
    global result_window, result_label

    if result_window is None:
        result_window = tk.Tk()
        result_window.title("Bluetooth Data Result")

        result_window.geometry("1000x500")

        result_label = tk.Label(result_window, text="Waiting...", font=("Helvetica", 32), width=60, height=50)
        result_label.pack(expand=True)

    if not result_window.winfo_ismapped():
        result_window.after(100, result_window.deiconify)

def update_result_window(message, bg_color):
    if result_label:
        result_label.config(text=message, bg=bg_color)

def read_bluetooth_data(dev):
    pressure_char_uuid = "2A19"
    pressure_char = dev.getCharacteristics(uuid=pressure_char_uuid)[0]

    try:
        while True:
            pressure_value = pressure_char.read().decode('utf-8')
            print("Pressure Value:", pressure_value)

            try:
                pressure_value_int = int(pressure_value)

                if pressure_value_int > 2000:
                    update_result_window("Yes", "green") 
                else:
                    update_result_window("No", "red") 

            except ValueError:
                print("Received non-integer pressure value:", pressure_value)

    except KeyboardInterrupt:
        print("Disconnected")
        dev.disconnect()

device_address = "EC:C9:FF:E1:7D:42"

print("Connecting to BLE device...")
dev = Peripheral(device_address)

bluetooth_thread = threading.Thread(target=read_bluetooth_data, args=(dev,))
bluetooth_thread.daemon = True
bluetooth_thread.start()

create_result_window()

try:
    result_window.mainloop()

except KeyboardInterrupt:
    print("Program exited")
