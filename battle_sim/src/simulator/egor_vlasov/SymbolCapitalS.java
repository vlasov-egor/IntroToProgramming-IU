package simulator.egor_vlasov;

import simulator.do_not_change.Symbol;
import simulator.do_not_change.Aggressive;
import simulator.do_not_change.CapitalCase;
import simulator.do_not_change.Position;
import java.util.Random;

public class SymbolCapitalS extends Symbol implements Aggressive, CapitalCase {
    public final int UPGRADE_ITERATIONS = 50;
    public final int DIE_ITERATIONS = 100;

    public SymbolCapitalS(Position position, int sightDistance) {
        this.idSymbol = MyWorldController.lastId++;
        this.position = position;
        this.sightDistance = sightDistance;
        this.numberIterationsAlive = UPGRADE_ITERATIONS + 1;
    }

    public SymbolCapitalS(SymbolSmallR small) {
        this.idSymbol = small.getIdSymbol();
        this.position = small.getPosition();
        this.sightDistance = small.getSightDistance() + 1;
        this.numberIterationsAlive = small.getNumberIterationsAlive() + 1;
    }

    @Override
    public void move() {
        int currentX = this.getPosition().x;
        int currentY = this.getPosition().y;
        Position[] possiblePositions = new Position[((2 * sightDistance) + 1) * ((2 * sightDistance) + 1) - 1];

        for (int i = 0; i < sightDistance; ++i) {
            for (int j = 0; j < sightDistance; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }

                possiblePositions[i] = new Position(currentX + i, currentY + j);
            }
        }

        this.setPosition(possiblePositions[0
                + (int) (Math.random() * ((2 * sightDistance) + 1) * ((2 * sightDistance) + 1) - 1)]);
    }

    @Override
    public void die() {
        System.out.println("I died");
    }

    @Override
    public void attackSmart() {
        int currentX = this.getPosition().x;
        int currentY = this.getPosition().y;
        Position[] possiblePositions = new Position[((2 * sightDistance) + 1) * ((2 * sightDistance) + 1) - 1];

        for (int i = 0; i < sightDistance; ++i) {
            for (int j = 0; j < sightDistance; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }

                // так заебись? или хуево?
                LinkedList symbolsInCurrentCoord = MyWorldController.world
                        .get(new Position(currentX + i, currentY + j));

                if (symbolsInCurrentCoord.indexOf("p") == -1 && symbolsInCurrentCoord.indexOf("P") == -1) {
                    continue;
                } else {
                    possiblePositions[i] = new Position(currentX + i, currentY + j);
                }
            }
        }
        //  TODO проверка на пустоту
        this.setPosition(possiblePositions[0 + (int) (Math.random() * possiblePositions.length)]);
    }

    @Override
    public void jump() {
        System.out.println("jump");
        System.out.println(this.getPosition());
        int randomX = 0 + (int) (Math.random() * 9);
        int randomY = 0 + (int) (Math.random() * 9);

        Position newPosition = new Position(randomX, randomY);
        this.setPosition(newPosition);
    }
}
