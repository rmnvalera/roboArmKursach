package utils;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ArduinoUtil {

    private final Logger logger = LoggerFactory.getLogger(ArduinoUtil.class);
    private Arduino arduino;
    private String port;
    private int baud_rate;

    public ArduinoUtil(String port, int baud_rate) {
        this.port = port;
        this.baud_rate = baud_rate;
    }

    public Arduino getArduino() {
        return arduino;
    }

    public void init() {
        arduino = new Arduino(port, baud_rate);
//        checkconnection();
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void checkconnection(){
        boolean connected = arduino.openConnection();

        if (!connected) {
            logger.info("Arduino Connection: " + connected);
            System.exit(1);
        } else {
            logger.info("Arduino Connection established: " + connected);
        }
    }
}
