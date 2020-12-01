package numbers.src.numbers.egor_vlasov;

import numbers.src.numbers.egor_vlasov.MyNumberCreator;
import numbers.do_not_change.Calculator;

import java.util.ArrayList;
import java.util.List;

import org.graalvm.compiler.core.common.type.ArithmeticOpTable.UnaryOp.Sqrt;

import java.math.*;

public class MyCalculator extends Calculator {

    /**
     * This method allows summarizing all elements of the input list of numbers
     *
     * @return the double sum of all elements
     */
    public double summarize() {
        List<Number> numbers = getNumbers();
        double sum = 0;
        for (int i : numbers) {
            sum += i;
        }

        return sum;
    }

    /**
     * This method allows multiplying all elements of the input list of numbers
     *
     * @return the double result of all element multiplication
     */
    public double multiply() {
        List<Number> numbers = getNumbers();
        double product = 1;
        for (int i : numbers) {
            product *= i;
        }

        return product;
    }

    /**
     * This method allows deleting all negative numbers from the list
     */
    public void deleteNegativeNumbers() {
        List<Number> numbers = getNumbers();
        for (int i = 0; i < numbers.size(); ++i) {
            if (numbers[i] < 0) {
                numbers.remove(i);
            }
        }
    }

    /**
     * This method allows dividing each number of the list by the divisor and
     * rewrite the list values
     *
     * @param divisor the divisor
     */
    public void divideBy(double divisor) {
        List<Number> numbers = getNumbers();
        try {
            for (int i = 0; i < numbers.size(); ++i) {
                numbers[i] /= divisor;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * This method allows calculating square root for each element of the array and
     * updating the list values
     */
    public void getSquareRoot() {
        List<Number> numbers = new ArrayList<Number>(getNumbers());
        try {
            for (int i = 0; i < numbers.size(); ++i) {
                numbers[i] = Math.sqrt(numbers[i]);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
