package numbers.src.numbers.egor_vlasov;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;
import java.util.InputMismatchException;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.stream.Stream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import numbers.do_not_change.NumberCreator;

public class MyNumberCreator extends NumberCreator {
    public static int getRandomNumber(int min, int max) {
        return (int) ((Math.random() * (max - min)) + min);
    }

    /**
     * This method allows to choose the size of list with numbers by scanning it
     *
     * @return the quantity of numbers in the list
     */
    @Override
    public int validateAndSetNumberQuantity() {
        Scanner input = new Scanner(System.in);

        try {
            int quantity = input.nextInt();
            if (MIN_NUMBER_QUANTITY > quantity || quantity > MAX_NUMBER_QUANTITY) {
                throw new Exception("");
            }
            return quantity;
        } catch (Exception exception) {
            System.out.println("Wrong quantity");
            return validateAndSetNumberQuantity();
        } catch (InputMismatchException e) {
            input.next();
            return validateAndSetNumberQuantity();
        }
    }

    /**
     * This method allows generating the list of numbers of different types
     *
     * @param numberQuantity the quantity of numbers in the list
     * @return the list of generated numbers
     */
    @Override
    public List<Number> generateNumbers(int numberQuantity) {
        List<Class<? extends Number>> classes = new ArrayList<Class<? extends Number>>(Arrays.asList(Short.class,
                Integer.class, Long.class, Float.class, Double.class, Byte.class, BigDecimal.class, BigInteger.class));
        List<Number> numbers = new ArrayList<Number>();

        for (int i = 0; i < numberQuantity; ++i) {
            try {
                Class<? extends Number> randomClass = classes.get(getRandomNumber(0, classes.size()));
                Method m = getValue(randomClass);
                Class pType = m.getParameterTypes()[0];
                Number randomNumber = NUMBER_LOWER_BOUNDARY + Math.random() * NUMBER_UPPER_BOUNDARY;
                Method cMethod = Number.class.getMethod(pType.getName() + "Value");
                numbers.add(randomClass.cast(m.invoke(randomClass, cMethod.invoke(randomNumber))));
            } catch (Exception e) {
                // TODO
                e.printStackTrace();
            }
        }

        return numbers;
    }

    /**
     * This method allows to insert numbers into the list of randomly chosen types.
     * The user has to print the values via console. The incorrectly printed data
     * has to be handled
     *
     * @return the list of numbers inserted by user
     */
    @Override
    public List<Number> insertNumbers(int numberQuantity) {
        List<Number> numbers = new ArrayList<Number>();

        for (int i = 0; i < numberQuantity; i++) {
            numbers.add(readNumber());
        }
    }

    private Number readNumber() {
        Scanner input = new Scanner(System.in);
        List<Class<? extends Number>> classes = new ArrayList<Class<? extends Number>>(Arrays.asList(BigDecimal.class,
                BigInteger.class, Byte.class, Double.class, Float.class, Integer.class, Long.class, Short.class));

        try {
            Class<? extends Number> randomClass = classes.get(getRandomNumber(0, classes.size()));

            System.out.println("Enter " + randomClass.getSimpleName());
            String methodName = "next" + randomClass.getSimpleName();
            methodName = "nextInteger".equals(methodName) ? "nextInt" : methodName;
            return randomClass.cast((Scanner.class.getMethod(methodName).invoke(input)));
        } catch (InvocationTargetException e1) {
            input.next();
            return readNumber();
        } catch (Exception e) {
            e.printStackTrace();
            return readNumber();
        }
    }

    public <T> Method getValue(Class<T> c) {
        return Stream.of(c.getMethods()).filter(m -> m.getName() == "valueOf")
                .filter(m -> m.getParameterTypes()[0] != String.class).findFirst().get();
    }
}
