package simulator.egor_vlasov;

import simulator.do_not_change.*;
import simulator.egor_vlasov.*;
import simulator.egor_vlasov.Util;
import java.util.LinkedList;
import java.util.List;

public class SymbolSmallP extends Symbol implements Aggressive, SmallCase {

    public final int UPGRADE_ITERATIONS = 50;

    public SymbolSmallP(Position position, int sightDistance) {
        this.idSymbol = Symbol.COUNT_SYMBOLS++;
        this.position = position;
        this.sightDistance = sightDistance;
        this.numberIterationsAlive = 0;
    }

    @Override
    public void move() {
        int currentX = this.getPosition().column;
        int currentY = this.getPosition().row;
        List<Position> possiblePositions = new List();

        for (int i = 0; i < sightDistance; ++i) {
            for (int j = 0; j < sightDistance; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }

                possiblePositions.add(new Position(currentY + i, currentX + j));
            }
        }

        this.setPosition(possiblePositions[Util.getRandomNumber(0, possiblePositions.size())]);
    }

    @Override
    public void die() {
        System.out.println("I died");
    }

    @Override
    public void attackSmart() {
        int currentX = this.getPosition().column;
        int currentY = this.getPosition().row;
        List<Position> possiblePositions = new List();

        for (int i = 0; i < sightDistance; ++i) {
            for (int j = 0; j < sightDistance; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }

                // так заебись? или хуево?
                LinkedList symbolsInCurrentCoord = MyWorldController.world
                        .get(new Position(currentY + i, currentX + j));

                if (!Util.<SymbolSmallR>hasSymbol(symbolsInCurrentCoord)
                        && !Util.<SymbolCapitalR>hasSymbol(symbolsInCurrentCoord)) {
                    continue;
                } else {
                    possiblePositions.add(new Position(currentY + i, currentX + j));
                }
            }
        }
        // TODO проверка на пустоту
        this.setPosition(possiblePositions[Util.getRandomNumber(0, possiblePositions.size())]);
    }

    @Override
    public void upgrade() {
        MyWorldController.world.get(this.getPosition()).add(new SymbolCapitalP(this));
    }
}
