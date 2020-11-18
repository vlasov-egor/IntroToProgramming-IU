package simulator.egor_vlasov;

import simulator.egor_vlasov.MyWorldController;
import simulator.do_not_change.Position;
import simulator.do_not_change.Symbol;
import java.util.stream.*;
import java.util.LinkedList;
import java.util.List;

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
        System.out.print("dsd");
    }

    public void setStage(String stage) {

    }

    public void tick() {
        // Move fucking letters;
        setStage("Moving symbols");
        Stream<Symbol> stream = Stream.empty();
        for (int x = 0; x <= 10; x++) {
            for (int y = 0; y <= 10; y++) {
                stream = Stream.concat(stream, MyWorldController.world.get(new Position(y, x)).stream());
                MyWorldController.world.put(new Position(y, x), new LinkedList());
            }
        }
        List<Symbol> symbolsToMove = stream.collect(Collectors.toList());
        controller.symbolsMove(symbolsToMove);
        draw();
        // waitFiveFuckingSeconds();
    }
}
