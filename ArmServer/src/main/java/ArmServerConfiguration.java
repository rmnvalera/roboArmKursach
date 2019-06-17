import io.dropwizard.Configuration;
import org.hibernate.validator.constraints.NotEmpty;

public class ArmServerConfiguration extends Configuration {

    public String getTemplate() {
        return template;
    }

    @NotEmpty
    private String template;

}
