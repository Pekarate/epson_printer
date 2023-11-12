import serial

com_port = 'COM10'  # Replace with the actual COM port you want to use (COM10 in this case)
baud_rate = 9600  # Adjust the baud rate as needed

# Define the initial 7-byte hexadecimal data as a list of integers
initial_data = [0x1B, 0x28, 0x73, 0x04,0x00, 0x31, 0x42]

try:
    ser = serial.Serial(com_port, baud_rate,dsrdtr=True)
    for i in range(60000,65536):
        # Calculate the two bytes to be added
        last_two_bytes = [i // 256, i % 256]

        # Combine the initial data with the changing bytes
        hex_data = initial_data + last_two_bytes

        # Convert the hexadecimal data to bytes
        hex_bytes = bytes(hex_data)

        # Write the hexadecimal data to the COM port
        ser.write(hex_bytes)

        # Read data from the COM port
        received_data = ser.read(20)  # Read 10 bytes of data (adjust as needed)
        trimmed_data = received_data[3:-1]
        # Append the received data to the file
        with open('command42_6xxxx.c', 'ab') as file:
            file.write(b'"' + trimmed_data + b'",\n')

    # Close the COM port after the loop
    ser.close()

except serial.SerialException:
    print(f"Failed to open {com_port}. Make sure it's available and not in use.")
