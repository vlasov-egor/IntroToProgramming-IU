package simulator.egor_vlasov;

import simulator.do_not_change.Symbol;
import java.util.List;

public class Util {
    public static <T extends Symbol> boolean hasSymbol(List<Symbol> list) {
        Class type = ((T) new Object()).getClass();

        return list.stream().filter(o -> type.isInstance(o)).findFirst().isPresent();
    }

    public static int getRandomNumber(int min, int max) {
        return (int) ((Math.random() * (max - min)) + min);
    }
}
