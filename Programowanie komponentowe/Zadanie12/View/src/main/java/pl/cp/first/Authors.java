package pl.cp.first;

import java.util.ListResourceBundle;

public class Authors extends ListResourceBundle {

    @Override
    protected Object[][] getContents() {
        return new Object[][]{
                {"1", "Wiktor Bechciński ",},
                {"2", "Kamil Budzyn "}
        };
    }
}
