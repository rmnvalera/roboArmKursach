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

@Path("/v1/motor")
@Produces(MediaType.APPLICATION_JSON)
public class MotorController {

    private final Logger logger = LoggerFactory.getLogger(MotorController.class);

    public MotorController() {
    }

    @GET
    @Timed
    public Response motorHandler(@QueryParam("number") int number,
                                 @QueryParam("turnckw") boolean turnckw,
                                 @QueryParam("step") boolean step) {
        if (number == 0) {
            logger.warn("number motor = 0");
            return Response.status(404).build();
        }
        if (number > 3) {
            logger.warn("number motor does not exist");
            return Response.status(404).build();
        }




        return Response.ok().build();
    }
}
