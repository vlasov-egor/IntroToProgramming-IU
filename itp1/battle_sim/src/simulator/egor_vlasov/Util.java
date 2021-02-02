package simulator.egor_vlasov;

import simulator.do_not_change.Symbol;
import java.util.List;
import java.util.ArrayList;
import java.lang.reflect.*;

public class Util {
    /**
     * Check if list has instance of class.
     * 
     * @param list list where look for the instance
     * @param type class to look for the class instance
     * @return true, if list contains instance and otherwise false
     */
    public static <T extends Symbol> boolean hasSymbol(List<Symbol> list, Class<T> type) {
        return list.stream().filter(o -> type.isInstance(o)).findFirst().isPresent();
    }

    /**
     * Generates random number in range
     * 
     * @param min lower bound of range
     * @param predicate upper bound of range
     * @return random number in range
     */
    public static int getRandomNumber(int min, int max) {
        return (int) ((Math.random() * (max - min)) + min);
    }
}
