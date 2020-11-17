package simulator.egor_vlasov;

import simulator.do_not_change.Symbol;
import simulator.do_not_change.CapitalCase;
import simulator.do_not_change.Passive;

public class SymbolCapitalP extends Symbol implements Passive, CapitalCase {
    public final int UPGRADE_ITERATIONS = 50;
    public final int DIE_ITERATIONS = 100;

    public SymbolCapitalP(Position position, int sightDistance) {
        this.idSymbol = MyWorldController.lastId++;
        this.position = position;
        this.sightDistance = sightDistance;
        this.numberIterationsAlive = UPGRADE_ITERATIONS + 1;
    }

    public SymbolCapitalP(SymbolSmallR small) {
        this.idSymbol = small.getIdSymbol();
        this.position = small.getPosition();
        this.sightDistance = small.getSightDistance() + 1;
        this.numberIterationsAlive = small.getNumberIterationsAlive() + 1;
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
    public void jump() {

    }
}
