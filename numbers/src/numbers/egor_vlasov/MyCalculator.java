package numbers.egor_vlasov;

import numbers.egor_vlasov.MyNumberCreator;
import numbers.do_not_change.Calculator;

import java.util.ArrayList;
import java.util.List;

import java.math.*;

public class MyCalculator extends Calculator {
    public MyCalculator(List<Number> numbers) {
        super(numbers);
    }

    /**
     * This method allows summarizing all elements of the input list of numbers
     *
     * @return the double sum of all elements
     */
    public double summarize() {
        List<Number> numbers = new ArrayList<Number>(getNumbers());
        double sum = 0;
        for (int i = 0; i < numbers.size(); ++i) {
            sum += numbers.get(i).doubleValue();
        }

        return sum;
    }

    /**
     * This method allows multiplying all elements of the input list of numbers
     *
     * @return the double result of all element multiplication
     */
    public double multiply() {
        List<Number> numbers = new ArrayList<Number>(getNumbers());
        double product = 1;
        for (int i = 0; i < numbers.size(); ++i) {
            product *= numbers.get(i).doubleValue();
        }

        return product;
    }

    /**
     * This method allows deleting all negative numbers from the list
     */
    public void deleteNegativeNumbers() {
        List<Number> numbers = new ArrayList<Number>(getNumbers());
        for (int i = 0; i < numbers.size(); ++i) {
            if (numbers.get(i).doubleValue() < 0) {
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
        List<Number> numbers = new ArrayList<Number>(getNumbers());
        try {
            for (int i = 0; i < numbers.size(); ++i) {
                numbers.set(i, numbers.get(i).doubleValue() / divisor);
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
                numbers.set(i, Math.sqrt(numbers.get(i).doubleValue()));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
