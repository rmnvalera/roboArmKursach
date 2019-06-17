import com.fasterxml.jackson.annotation.JsonProperty;
import configuration.ArduinoConfiguration;
import io.dropwizard.Configuration;
import org.hibernate.validator.constraints.NotEmpty;


public class ArmServerConfiguration extends Configuration {

    @NotEmpty
    private String template;

    @JsonProperty
    private ArduinoConfiguration arduino;

    public String getTemplate() {
        return template;
    }

    public ArduinoConfiguration getArduinoConfiguration() {
        return arduino;
    }

}
