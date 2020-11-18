package simulator.egor_vlasov;

import simulator.do_not_change.Symbol;
import java.util.List;
import java.util.ArrayList;
import java.lang.reflect.*;

public class Util {
    public static <T extends Symbol> boolean hasSymbol(List<Symbol> list, Class<T> type) {
        return list.stream().filter(o -> type.isInstance(o)).findFirst().isPresent();
    }

    public static int getRandomNumber(int min, int max) {
        return (int) ((Math.random() * (max - min)) + min);
    }
}
