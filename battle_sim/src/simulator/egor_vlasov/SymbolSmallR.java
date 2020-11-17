package simulator.egor_vlasov;

import simulator.do_not_change.Symbol;
import simulator.do_not_change.Passive;
import simulator.do_not_change.SmallCase;
import simulator.do_not_change.Position;

public class SymbolSmallR extends Symbol implements Passive, SmallCase {

    public final int UPGRADE_ITERATIONS = 50;

    public SymbolSmallR(Position position, int sightDistance) {
        this.idSymbol = MyWorldController.lastId++;
        this.position = position;
        this.sightDistance = sightDistance;
        this.numberIterationsAlive = 0;
    }

    @Override
    public void move() {

    }

    @Override
    public void die() {

    }

    @Override
    public void escape() {

    }

    @Override
    public void moveBreed() {

    }

    @Override
    public void upgrade() {
        MyWorldController.world.put(this.getPosition(), new SymbolCapitalR(this));
    }
}
