package an;

import java.nio.charset.StandardCharsets;

import jssc.SerialPort;
import jssc.SerialPortException;

public class Main {
	
	public static void main(String[] args) {
		int ultra_val, light_val, pir_val;
		SerialPort serialPort = new SerialPort("COM7");
		try {
			serialPort.openPort();// Open serial port
			serialPort.setParams(9600, 8, 1, 0);// Set params.
			int i = 100;
			while (i>0) {
				i--;
				byte[] buffer = serialPort.readBytes(35);// Read 10 bytes from serial port
				String str = new String(buffer, StandardCharsets.UTF_8);
				//System.out.print(str);
				String tmp = str.substring(0, 1);
				pir_val = Integer.parseInt(tmp, 2);
				tmp = str.substring(1, 17);
				light_val = Integer.parseInt(tmp, 2);
				tmp = str.substring(17,33);
				ultra_val = Integer.parseInt(tmp, 2);
				System.out.println("적외선 센서 : "+pir_val+", 조도 센서 : "+light_val+", 초음파 센서 : "+ultra_val);
			}
			serialPort.closePort();// Close serial port
		} catch (SerialPortException ex) {
			System.out.println(ex);
		}
	}
}