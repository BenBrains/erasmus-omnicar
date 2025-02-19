# Create an instance of the main window and run the main loop
# When a key is pressed write this to a bluetooth device

import tkinter as tk
import socket
import sys
import argparse

PULSETIME = 5

parser = argparse.ArgumentParser(description="Bluetooth Keyboard")
parser.add_argument("-m", "--mac", type=str, default="CC:DB:A7:9F:8B:0E", help="MAC address of the Bluetooth device")
args = parser.parse_args()

MACADD = args.mac

def connect_to_bluetooth_device(mac_address):
    try:
        # Create the client socket
        sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
        
        # Connect to the device
        sock.connect((mac_address, 1))
        print(f"Connected to {mac_address}")
        
        return sock
    except Exception as err:
        print(f"Failed to connect: {err}")
        return None

class MainWindow(tk.Tk):
    
    # Buttons held down
    buttons = []
    
    def __init__(self):
        super().__init__()
        self.title("Bluetooth Keyboard")
        self.geometry("400x200")
        self.bind("<KeyPress>", self.on_key_press)
        self.bind("<KeyRelease>", self.on_key_release)
        
        # Add box to display a message from the bluetooth device
        self.text = tk.Text(self, state='disabled')
        self.text.pack()
        
        # Every frame we will write the keys to the bluetooth device
        self.after(PULSETIME, self.write)
        # self.after(PULSETIME, self.read)
        
        self.sock = connect_to_bluetooth_device(MACADD)
    
    def read(self):
        try:
            data = self.sock.recv(1024)
            print(data.decode())
            
        except Exception as err:
            print(f"Failed to read data: {err}")
        self.after(PULSETIME, self.read)
        
    def write(self):
        but = self.buttons
        but.sort()
        print(but)
        if self.sock:
            try:
                # Check if the connection is still active
                self.sock.send(b"")
            except Exception as err:
                print(f"Connection lost: {err}")
                while True:
                    try:
                        self.sock = connect_to_bluetooth_device(MACADD)
                        break
                    except:
                        print("Failed to reconnect")
                        pass
                
            try:
                if len(but) > 0:
                    for button in but:
                        self.sock.send(button.encode())
                    self.sock.send("~".encode())
                else:
                    self.sock.send("0~".encode())
            except Exception as err:
                print(f"Failed to send data: {err}")
        
        self.after(PULSETIME, self.write)

    def recreate_socket(self):
        if(self.sock):
            self.sock.close()
        self.sock = connect_to_bluetooth_device(MACADD)
        
        
    def on_key_press(self, event):
        if(event.keysym == "Escape"):
            self.destroy()
        if(event.keysym == "r"):
            self.recreate_socket()
        if event.keysym not in self.buttons:
            self.buttons.append(event.keysym)
            
    def on_key_release(self, event):
        if event.keysym in self.buttons:
            self.buttons.remove(event.keysym)

if __name__ == "__main__":
    window = MainWindow()
    window.mainloop()