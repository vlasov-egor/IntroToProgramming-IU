package simulator.egor_vlasov;

import simulator.egor_vlasov.MyWorldController;
import java.util.Stream;
import java.util.LinkedList;
import java.util.Collectors;

public class Simulator extends Object {
    MyWorldController controller;

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
        system.out.print("dsd");
    }

    public void setStage(String stage) {

    }

    public void tick() {
        // Move fucking letters;
        setStage("Moving symbols");
        Stream stream = Stream.empty();
        for (int x = 0; x <= 10; x++) {
            for (int y = 0; y <= 10; y++) {
                stream = Stream.concat(stream, MyWorldController.world.get(new Position(x, y)).stream());
                MyWorldController.world.put(new Position(x, y), new LinkedList());
            }
        }
        controller.symbolsMove(stream.collect(Collectors.toList()));
        draw();
        // waitFiveFuckingSeconds();
    }
}
