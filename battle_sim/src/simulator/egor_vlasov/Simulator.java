package simulator.egor_vlasov;

import simulator.egor_vlasov.MyWorldController;
import simulator.do_not_change.*;
import java.util.stream.*;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Map;
import java.util.function.*;

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

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
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

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    public void setStage(String stage) {
        System.out.println("");
        System.out.println("-".repeat(stage.length() + 10));
        System.out.println("|    " + stage + "    |");
        System.out.println("-".repeat(stage.length() + 10));
        System.out.println("");
    }

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
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

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    void die() {
        setStage("Symbols die");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                Stream<Symbol> cell = MyWorldController.world.get(new Position(y, x)).stream();
                Map<Boolean, List<Symbol>> cellSplitted = cell.collect(Collectors.partitioningBy(s -> {
                    if (s instanceof SymbolCapitalP
                            && ((SymbolCapitalP) s).DIE_ITERATIONS == s.getNumberIterationsAlive()) {
                        return true;
                    }
                    if (s instanceof SymbolCapitalR
                            && ((SymbolCapitalR) s).DIE_ITERATIONS == s.getNumberIterationsAlive()) {
                        return true;
                    }
                    if (s instanceof SymbolCapitalS
                            && ((SymbolCapitalS) s).DIE_ITERATIONS == s.getNumberIterationsAlive()) {
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

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    ArrayList<Symbol>[] split(ArrayList<Symbol> list, Predicate<Symbol> predicate) {
        ArrayList<Symbol>[] splitArr = new ArrayList[2];

        splitArr[0] = new ArrayList();
        splitArr[1] = new ArrayList();

        for (Symbol o: list) {
            if (predicate.test(o)) {
                splitArr[0].add(o);
            } else {
                splitArr[1].add(o);
            }
        }

        return splitArr;
    }

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    void fight() {
        setStage("Symbols fight");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                ArrayList<Symbol> toDie = new ArrayList();
                ArrayList<Symbol> cell = new ArrayList(MyWorldController.world.get(new Position(y, x)));

                if (cell.size() == 0) {
                    continue;
                }

                if (Util.hasSymbol(cell, SymbolCapitalR.class) || Util.hasSymbol(cell, SymbolSmallR.class)) {
                    ArrayList<Symbol>[] splitted = split(cell,
                            s -> (s instanceof SymbolCapitalS) || (s instanceof SymbolSmallS));

                    toDie.addAll(splitted[0]);
                    cell = splitted[1];
                }

                if (Util.hasSymbol(cell, SymbolCapitalP.class) || Util.hasSymbol(cell, SymbolSmallP.class)) {
                    ArrayList<Symbol>[] splitted = split(cell,
                            s -> (s instanceof SymbolCapitalR) || (s instanceof SymbolSmallR));

                    toDie.addAll(splitted[0]);
                    cell = splitted[1];
                }

                if (Util.hasSymbol(cell, SymbolCapitalS.class) || Util.hasSymbol(cell, SymbolSmallS.class)) {
                    ArrayList<Symbol>[] splitted = split(cell,
                            s -> (s instanceof SymbolCapitalP) || (s instanceof SymbolSmallP));

                    toDie.addAll(splitted[0]);
                    cell = splitted[1];
                }

                stream = Stream.concat(stream, toDie.stream());

                LinkedList ll = new LinkedList();
                ll.addAll(cell);
                MyWorldController.world.put(new Position(y, x), ll);
            }
        }

        List<Symbol> symbolsToDie = stream.collect(Collectors.toList());
        controller.symbolsDie(symbolsToDie);

        draw();

    }

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    void becomeOlder() {
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                MyWorldController.world.get(new Position(y, x)).stream().forEach(s -> s.becomeOlder());
            }
        }
    }

    void upgrade() {
        setStage("Symbols upgrade");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                Stream<Symbol> cell = MyWorldController.world.get(new Position(y, x)).stream();
                Map<Boolean, List<Symbol>> cellSplitted = cell.collect(Collectors.partitioningBy(s -> {
                    if (s instanceof SymbolSmallP
                            && ((SymbolSmallP) s).UPGRADE_ITERATIONS == s.getNumberIterationsAlive()) {
                        return true;
                    }
                    if (s instanceof SymbolSmallR
                            && ((SymbolSmallR) s).UPGRADE_ITERATIONS == s.getNumberIterationsAlive()) {
                        return true;
                    }
                    if (s instanceof SymbolSmallS
                            && ((SymbolSmallS) s).UPGRADE_ITERATIONS == s.getNumberIterationsAlive()) {
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

        List<SmallCase> symbolsToUpgrade = stream.map(s -> (SmallCase)s).collect(Collectors.toList());
        controller.smallCaseUpgrade(symbolsToUpgrade);
        draw();
    }

    void sex() {
        setStage("Symbols sex");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                LinkedList ll = MyWorldController.world.get(new Position(y, x));

                long CapitalP_Count = ll.stream().filter(s -> s instanceof SymbolCapitalP).count();
                long CapitalR_Count = ll.stream().filter(s -> s instanceof SymbolCapitalR).count();
                long CapitalS_Count = ll.stream().filter(s -> s instanceof SymbolCapitalS).count();
                long SmallP_Count = ll.stream().filter(s -> s instanceof SymbolSmallP).count();
                long SmallR_Count = ll.stream().filter(s -> s instanceof SymbolSmallR).count();
                long SmallS_Count = ll.stream().filter(s -> s instanceof SymbolSmallS).count();

                long pCount = CapitalP_Count / 2 + SmallP_Count / 2;
                long rCount = CapitalR_Count / 2 + SmallR_Count / 2;
                long sCount = CapitalS_Count / 2 + SmallS_Count / 2;
                
                for (long i = 0; i < pCount; i++) {
                    int randomSightDistance = Util.getRandomNumber(1, 5);
                    MyWorldController.world.get(new Position(y, x)).add(new SymbolSmallP(new Position(y, x), randomSightDistance));
                }

                for (long i = 0; i < rCount; i++) {
                    int randomSightDistance = Util.getRandomNumber(1, 5);
                    MyWorldController.world.get(new Position(y, x)).add(new SymbolSmallR(new Position(y, x), randomSightDistance));
                }

                for (long i = 0; i < sCount; i++) {
                    int randomSightDistance = Util.getRandomNumber(1, 5);
                    MyWorldController.world.get(new Position(y, x)).add(new SymbolSmallS(new Position(y, x), randomSightDistance));
                }
            }
        }

        draw();
    }

    void jump() {
        setStage("Symbols jump");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                ArrayList<Symbol> cell = new ArrayList(MyWorldController.world.get(new Position(y, x)));
                ArrayList<Symbol> toJump;

                ArrayList<Symbol>[] splitted = split(cell,
                            s -> (s instanceof SymbolCapitalP) || (s instanceof SymbolCapitalR) || (s instanceof SymbolCapitalS));

                toJump = splitted[0];
                cell = splitted[1];

                stream = Stream.concat(stream, toJump.stream());

                LinkedList ll = new LinkedList();
                ll.addAll(cell);
                MyWorldController.world.put(new Position(y, x), ll);
            }
        }

        List<CapitalCase> symbolsToJump = stream.map(s -> (CapitalCase)s).collect(Collectors.toList());
        controller.capitalCaseJump(symbolsToJump);
        draw();
    }

    void aggressiveAttack() {
        setStage("Symbols attack");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                ArrayList<Symbol> cell = new ArrayList(MyWorldController.world.get(new Position(y, x)));
                ArrayList<Symbol> toAttack;

                ArrayList<Symbol>[] splitted = split(cell,
                            s -> (s instanceof SymbolSmallP) || (s instanceof SymbolCapitalR) || (s instanceof SymbolCapitalS));

                toAttack = splitted[0];
                cell = splitted[1];

                stream = Stream.concat(stream, toAttack.stream());

                LinkedList ll = new LinkedList();
                ll.addAll(cell);
                MyWorldController.world.put(new Position(y, x), ll);
            }
        }

        List<Aggressive> symbolsToAttack = stream.map(s -> (Aggressive)s).collect(Collectors.toList());
        controller.aggressiveAttackSmart(symbolsToAttack);
        draw();
    }

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    public void tick() {
        move();
        // wait
        die();
        // wait
        upgrade();
        // wait
        fight();
        // wait
        jump();
        // wait
        sex();
        // wait
        aggressiveAttack();
        // wait
        becomeOlder();
    }
}
