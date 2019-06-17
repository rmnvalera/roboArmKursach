package controller;

import com.codahale.metrics.annotation.Timed;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import utils.Arduino;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;


@Path("/v1/servo")
@Produces(MediaType.APPLICATION_JSON)
public class ServoController {

    private Arduino arduino;
    private final Logger logger = LoggerFactory.getLogger(ServoController.class);

    public ServoController(Arduino arduino) {
        this.arduino = arduino;
    }

    @GET
    @Timed
    public Response servoHandler(@QueryParam("open") boolean open) {
        boolean connected = arduino.openConnection();
        if (!connected) {
            logger.warn("ArduinoConnection: " + connected);
            return Response.status(405).build();
        }

        if (open){
            logger.info("Servo open");
            arduino.serialWrite("so");
        }else{
            logger.info("Servo close");
            arduino.serialWrite("sc");
        }

        return Response.ok().build();
    }

}
