package configuration;

import org.hibernate.validator.constraints.NotEmpty;


public class ArduinoConfiguration {

    @NotEmpty
    private String port;

    @NotEmpty
    private int baudRate;


    public void setPort(String port) {
        this.port = port;
    }

    public void setBaudRate(int baudRate) {
        this.baudRate = baudRate;
    }

    public String getPort() {
        return port;
    }

    public int getBaudRate() {
        return baudRate;
    }
}
