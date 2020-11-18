package simulator.egor_vlasov;

import simulator.do_not_change.Symbol;
import java.util.LinkedList;

public class Util {
    public static <T extends Symbol> boolean hasSymbol(LinkedList<Symbol> list) {
        return list.stream().filter(o -> o instanceof T).findFirst().isPresent();
    }
}
