package simulator.egor_vlasov;

import simulator.egor_vlasov.MyWorldController;
import simulator.do_not_change.Position;
import simulator.do_not_change.Symbol;
import java.util.stream.*;
import java.util.LinkedList;
import java.util.List;
import java.util.Arrays;
import java.util.Map;
import java.util.functions.*;

public class Simulator extends Object {
    MyWorldController controller;
    final int TICK_COUNT = 1000;

    public Simulator() {
        this.controller = new MyWorldController();
    }

    public static void main(String[] args) {
        (new Simulator()).run();
    }

    public void run() {
        for (int i = 0; i < TICK_COUNT; i++) {
            tick();
        }
    }

    public void draw() {
        int[] length = new int[MyWorldController.MAX_COLS];

        for (int y = 0; y < MyWorldController.MAX_ROWS; y++) {
            for (int x = 0; x < MyWorldController.MAX_COLS; x++) {
                Position current = new Position(y, x);

                if (controller.world.get(current).size() > length[x]) {
                    length[x] = controller.world.get(current).size();
                }
            }
        }

        int sumlen = Arrays.stream(length).sum() + (MyWorldController.MAX_COLS) * 3 + 1;

        System.out.println("-".repeat(sumlen));
        for (int y = 0; y < MyWorldController.MAX_ROWS; y++) {
            System.out.print("| ");
            for (int x = 0; x < MyWorldController.MAX_COLS; x++) {
                Position current = new Position(y, x);
                controller.world.get(current).stream().forEach(o -> {
                    if (o instanceof SymbolCapitalP)
                        System.out.print(MyWorldController.CAPITAL_P);
                    if (o instanceof SymbolCapitalR)
                        System.out.print(MyWorldController.CAPITAL_R);
                    if (o instanceof SymbolCapitalS)
                        System.out.print(MyWorldController.CAPITAL_S);
                    if (o instanceof SymbolSmallP)
                        System.out.print(MyWorldController.SMALL_P);
                    if (o instanceof SymbolSmallR)
                        System.out.print(MyWorldController.SMALL_R);
                    if (o instanceof SymbolSmallS)
                        System.out.print(MyWorldController.SMALL_S);
                });

                System.out.print(" ".repeat(length[x] - controller.world.get(current).size()));
                System.out.print(" | ");
            }
            System.out.println();
            System.out.println("-".repeat(sumlen));
        }
    }

    public void setStage(String stage) {
        System.out.println("");
        System.out.println("-".repeat(stage.length() + 10));
        System.out.println("|    " + stage + "    |");
        System.out.println("-".repeat(stage.length() + 10));
        System.out.println("");
    }

    // Move fucking letters;
    void move() {
        setStage("Symbols move");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                stream = Stream.concat(stream, MyWorldController.world.get(new Position(y, x)).stream());
                MyWorldController.world.put(new Position(y, x), new LinkedList());
            }
        }
        List<Symbol> symbolsToMove = stream.collect(Collectors.toList());
        controller.symbolsMove(symbolsToMove);
        draw();
    }

    void die() {
        setStage("Symbols die");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                Stream<Symbol> cell = MyWorldController.world.get(new Position(y, x)).stream();
                Map<Boolean, List<Symbol>> cellSplitted = cell.collect(Collectors.partitioningBy(s -> {
                    if (s instanceof SymbolCapitalP && ((SymbolCapitalP) s).DIE_ITERATIONS == s.getNumberIterationsAlive()) {
                        return true;
                    }
                    if (s instanceof SymbolCapitalR && ((SymbolCapitalR) s).DIE_ITERATIONS == s.getNumberIterationsAlive()) {
                        return true;
                    }
                    if (s instanceof SymbolCapitalS && ((SymbolCapitalS) s).DIE_ITERATIONS == s.getNumberIterationsAlive()) {
                        return true;
                    }

                    return false;
                }));

                LinkedList ll = new LinkedList();
                ll.addAll(cellSplitted.get(false));

                MyWorldController.world.put(new Position(y, x), ll);
                stream = Stream.concat(stream, cellSplitted.get(true).stream());
            }
        }

        List<Symbol> symbolsToDie = stream.collect(Collectors.toList());
        controller.symbolsDie(symbolsToDie);
        draw();
    }

    List<Symbol>[] split(Predicate<Symbol> predicate) {

    }

    void fight() {
        setStage("Symbols fight");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                List<Symbol> toDie = new ArrayList();
                List<Symbol> cell = MyWorldController.world.get(new Position(y, x));

                if (Util.<SymbolCapitalR>hasSymbol(cell) || Util.<SymbolSmallR>hasSymbol(cell)) {

                }

                
                stream = Stream.concat(stream, cellSplitted.get(true).stream());
            }
        }

        List<Symbol> symbolsToDie = stream.collect(Collectors.toList());
        controller.symbolsDie(symbolsToDie);
        draw();
    }

    void becomeOlder() {
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                MyWorldController.world.get(new Position(y, x)).stream().forEach(s -> s.becomeOlder());
            }
        }
    }

    public void tick() {
        move();
        // wait
        die();
        // wait
        fight();
        // wait
        becomeOlder();
    }
}
