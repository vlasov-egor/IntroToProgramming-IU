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
import java.util.Collections;

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

            if (population() == 0) {
                break;
            }
        }
    }

    public int population() {
        int pop = 0;

        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                Position current = new Position(y, x);

                pop += controller.world.get(current).size();
            }
        }

        return pop;
    }

    /**
     * Prints board to console
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

        System.out.println(String.join("", Collections.nCopies(sumlen, "-")));
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

                System.out.print(String.join("", Collections.nCopies(length[x] - controller.world.get(current).size(), " ")));
                System.out.print(" | ");
            }
            System.out.println();
            System.out.println(String.join("", Collections.nCopies(sumlen, "-")));
        }
    }

    /**
     * Prints stage name
     */
    public void setStage(String stage) {
        System.out.println("");
        System.out.println(String.join("", Collections.nCopies(stage.length() + 10, "-")));
        System.out.println("|    " + stage + "    |");
        System.out.println(String.join("", Collections.nCopies(stage.length() + 10, "-")));
        System.out.println("");
    }

    /**
     * Moves all obects
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
     * Kills symbols that too old
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
     * Split list on two based on given predicate function
     * 
     * @param list      list of all symbols
     * @param predicate function used for dividing list
     * @return two lists
     */
    ArrayList<Symbol>[] split(ArrayList<Symbol> list, Predicate<Symbol> predicate) {
        ArrayList<Symbol>[] splitArr = new ArrayList[2];

        splitArr[0] = new ArrayList();
        splitArr[1] = new ArrayList();

        for (Symbol o : list) {
            if (predicate.test(o)) {
                splitArr[0].add(o);
            } else {
                splitArr[1].add(o);
            }
        }

        return splitArr;
    }

    /**
     * Performs fight logic
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

                if ((Util.hasSymbol(cell, SymbolCapitalR.class) || Util.hasSymbol(cell, SymbolSmallR.class))
                        && (Util.hasSymbol(cell, SymbolCapitalP.class) || Util.hasSymbol(cell, SymbolSmallP.class))
                        && (Util.hasSymbol(cell, SymbolCapitalS.class) || Util.hasSymbol(cell, SymbolSmallS.class))) {
                    toDie = cell;
                    cell = new ArrayList();
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
     * Increases iterations alive counter
     */
    void becomeOlder() {
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                MyWorldController.world.get(new Position(y, x)).stream().forEach(s -> s.becomeOlder());
            }
        }
    }

    /**
     * Upgrades small symbols when needed
     */
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

        List<SmallCase> symbolsToUpgrade = stream.map(s -> (SmallCase) s).collect(Collectors.toList());
        controller.smallCaseUpgrade(symbolsToUpgrade);
        draw();
    }

    /**
     * Makes the population grow as Chinese.
     */
    void reproduction() {
        setStage("Symbols reproduction");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                LinkedList ll = MyWorldController.world.get(new Position(y, x));

                if (ll.size() > 5 || population() > 300) {
                    continue;
                }

                long CapitalP_Count = ll.stream().filter(s -> s instanceof SymbolCapitalP).count();
                long CapitalR_Count = ll.stream().filter(s -> s instanceof SymbolCapitalR).count();
                long CapitalS_Count = ll.stream().filter(s -> s instanceof SymbolCapitalS).count();
                long SmallP_Count = ll.stream().filter(s -> s instanceof SymbolSmallP).count();
                long SmallR_Count = ll.stream().filter(s -> s instanceof SymbolSmallR).count();
                long SmallS_Count = ll.stream().filter(s -> s instanceof SymbolSmallS).count();

                long pCount = (CapitalP_Count >= 2 | SmallP_Count >= 2) ? 1 : 0;
                long rCount = (CapitalR_Count >= 2 | SmallR_Count >= 2) ? 1 : 0;
                long sCount = (CapitalS_Count >= 2 | SmallS_Count >= 2) ? 1 : 0;

                for (long i = 0; i < pCount; i++) {
                    int randomSightDistance = Util.getRandomNumber(1, 5);
                    MyWorldController.world.get(new Position(y, x))
                            .add(new SymbolSmallP(new Position(y, x), randomSightDistance));
                }

                for (long i = 0; i < rCount; i++) {
                    int randomSightDistance = Util.getRandomNumber(1, 5);
                    MyWorldController.world.get(new Position(y, x))
                            .add(new SymbolSmallR(new Position(y, x), randomSightDistance));
                }

                for (long i = 0; i < sCount; i++) {
                    int randomSightDistance = Util.getRandomNumber(1, 5);
                    MyWorldController.world.get(new Position(y, x))
                            .add(new SymbolSmallS(new Position(y, x), randomSightDistance));
                }
            }
        }

        draw();
    }

    /**
     *  Makes capital symbols jump
     */
    void jump() {
        setStage("Symbols jump");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                ArrayList<Symbol> cell = new ArrayList(MyWorldController.world.get(new Position(y, x)));
                ArrayList<Symbol> toJump;

                ArrayList<Symbol>[] splitted = split(cell, s -> (s instanceof SymbolCapitalP)
                        || (s instanceof SymbolCapitalR) || (s instanceof SymbolCapitalS));

                toJump = splitted[0];
                cell = splitted[1];

                stream = Stream.concat(stream, toJump.stream());

                LinkedList ll = new LinkedList();
                ll.addAll(cell);
                MyWorldController.world.put(new Position(y, x), ll);
            }
        }

        List<CapitalCase> symbolsToJump = stream.map(s -> (CapitalCase) s).collect(Collectors.toList());
        controller.capitalCaseJump(symbolsToJump);
        draw();
    }

    /**
    *  Makes passive symbols escape
    */
    void escape() {
        setStage("Symbols escape");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                ArrayList<Symbol> cell = new ArrayList(MyWorldController.world.get(new Position(y, x)));
                ArrayList<Symbol> toJump;

                ArrayList<Symbol>[] splitted = split(cell, s -> (s instanceof SymbolSmallR)
                        || (s instanceof SymbolSmallS) || (s instanceof SymbolCapitalP));

                toJump = splitted[0];
                cell = splitted[1];

                stream = Stream.concat(stream, toJump.stream());

                LinkedList ll = new LinkedList();
                ll.addAll(cell);
                MyWorldController.world.put(new Position(y, x), ll);
            }
        }

        List<Passive> symbolsToEscape = stream.map(s -> (Passive) s).collect(Collectors.toList());
        controller.passiveEscape(symbolsToEscape);
        draw();
    }

    /**
     * Makes passive symbols breed
     */
    void breed() {
        setStage("Symbols breed");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                ArrayList<Symbol> cell = new ArrayList(MyWorldController.world.get(new Position(y, x)));
                ArrayList<Symbol> toJump;

                ArrayList<Symbol>[] splitted = split(cell, s -> (s instanceof SymbolSmallR)
                        || (s instanceof SymbolSmallS) || (s instanceof SymbolCapitalP));

                toJump = splitted[0];
                cell = splitted[1];

                stream = Stream.concat(stream, toJump.stream());

                LinkedList ll = new LinkedList();
                ll.addAll(cell);
                MyWorldController.world.put(new Position(y, x), ll);
            }
        }

        List<Passive> symbolsToBreeed = stream.map(s -> (Passive) s).collect(Collectors.toList());
        controller.passiveBreed(symbolsToBreeed);
        draw();
    }

    /**
     * Makes agressive symbols attack
     */
    void aggressiveAttack() {
        setStage("Symbols attack");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x < MyWorldController.MAX_ROWS; x++) {
            for (int y = 0; y < MyWorldController.MAX_COLS; y++) {
                ArrayList<Symbol> cell = new ArrayList(MyWorldController.world.get(new Position(y, x)));
                ArrayList<Symbol> toAttack;

                ArrayList<Symbol>[] splitted = split(cell, s -> (s instanceof SymbolSmallP)
                        || (s instanceof SymbolCapitalR) || (s instanceof SymbolCapitalS));

                toAttack = splitted[0];
                cell = splitted[1];

                stream = Stream.concat(stream, toAttack.stream());

                LinkedList ll = new LinkedList();
                ll.addAll(cell);
                MyWorldController.world.put(new Position(y, x), ll);
            }
        }

        List<Aggressive> symbolsToAttack = stream.map(s -> (Aggressive) s).collect(Collectors.toList());
        controller.aggressiveAttackSmart(symbolsToAttack);

        Stream<Symbol> stream2 = Stream.empty();
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

                stream2 = Stream.concat(stream2, toDie.stream());

                LinkedList ll = new LinkedList();
                ll.addAll(cell);
                MyWorldController.world.put(new Position(y, x), ll);
            }
        }

        List<Symbol> symbolsToDie = stream2.collect(Collectors.toList());
        controller.symbolsDie(symbolsToDie);

        draw();
    }

    /**
     * One tick of iteration.
     */
    public void tick() {
        move();
        die();
        upgrade();
        fight();
        jump();
        escape();
        breed();
        aggressiveAttack();
        reproduction();
        becomeOlder();
    }
}
