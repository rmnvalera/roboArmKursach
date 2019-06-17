package controller;

import com.codahale.metrics.annotation.Timed;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;


@Path("/v1/servo")
@Produces(MediaType.APPLICATION_JSON)
public class ServoController {

    private final Logger logger = LoggerFactory.getLogger(ServoController.class);

    public ServoController() {

    }

    @GET
    @Timed
    public Response servoHandler(@QueryParam("open") boolean open) {
        if (open){
            logger.info("Servo open");
        }else{
            logger.info("Servo close");
        }
        return Response.ok().build();
    }

}
