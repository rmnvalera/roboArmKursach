import controller.MotorController;
import controller.ServoController;
import health.TemplateHealthCheck;
import io.dropwizard.Application;
import io.dropwizard.setup.Bootstrap;
import io.dropwizard.setup.Environment;

public class ArmServer extends Application<ArmServerConfiguration> {

    public static void main(String[] args) throws Exception {
        new ArmServer().run(args);
    }

    @Override
    public String getName() {
        return "ArmServer";
    }

    @Override
    public void initialize(Bootstrap<ArmServerConfiguration> bootstrap) {
        // nothing to do yet
    }

    @Override
    public void run(ArmServerConfiguration configuration, Environment environment) throws Exception {
        final TemplateHealthCheck healthCheck = new TemplateHealthCheck(configuration.getTemplate());
        environment.healthChecks().register("template", healthCheck);

        ServoController servoController = new ServoController();
        MotorController motorController = new MotorController();

        environment.jersey().register(motorController);
        environment.jersey().register(servoController);
    }
}
