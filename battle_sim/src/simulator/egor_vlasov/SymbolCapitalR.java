package simulator.egor_vlasov;

import simulator.do_not_change.Symbol;
import simulator.do_not_change.Aggressive;
import simulator.do_not_change.CapitalCase;
import simulator.do_not_change.Position;
import simulator.egor_vlasov.SymbolSmallR;

public class SymbolCapitalR extends Symbol implements Aggressive, CapitalCase {
    public final int UPGRADE_ITERATIONS = 50;
    public final int DIE_ITERATIONS = 100;

    public SymbolCapitalR(Position position, int sightDistance) {
        this.idSymbol = MyWorldController.lastId++;
        this.position = position;
        this.sightDistance = sightDistance;
        this.numberIterationsAlive = UPGRADE_ITERATIONS + 1;
    }

    public SymbolCapitalR(SymbolSmallR small) {
        this.idSymbol = small.getIdSymbol();
        this.position = small.getPosition();
        this.sightDistance = small.getSightDistance() + 1;
        this.numberIterationsAlive = small.getNumberIterationsAlive() + 1;
    }

    @Override
    public void move() {
        //  съебывает куда-то в квадрате sightdist*2+1 * sightdist*2+1
    }

    @Override
    public void die() {
        //  умирает нахуй
        //  рофлан поминки
    }

    @Override
    public void attackSmart() {
        //  пиздит слабых в пределах sightdist
    }

    @Override
    public void jump() {
        //  съебывается как Порошенко из Украины
    }
}
