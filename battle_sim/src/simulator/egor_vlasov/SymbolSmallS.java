package simulator.egor_vlasov;

import simulator.do_not_change.Symbol;
import simulator.do_not_change.Passive;
import simulator.do_not_change.SmallCase;
import simulator.do_not_change.Position;

public class SymbolSmallS extends Symbol implements Passive, SmallCase {

    public final int UPGRADE_ITERATIONS = 50;

    public SymbolSmallS(Position position, int sightDistance) {
        this.idSymbol = MyWorldController.lastId++;
        this.position = position;
        this.sightDistance = sightDistance;
        this.numberIterationsAlive = 0;
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
    public void escape() {
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

                if (symbolsInCurrentCoord.indexOf("R") == -1 && symbolsInCurrentCoord.indexOf("r") == -1
                        && symbolsInCurrentCoord.indexOf("P") == -1 && symbolsInCurrentCoord.indexOf("p") == -1) {
                    possiblePositions[i] = new Position(currentX + i, currentY + j);
                } else {
                    continue;
                }
            }
        }
        // TODO проверка на пустоту
        this.setPosition(possiblePositions[0 + (int) (Math.random() * possiblePositions.length)]);
    }

    @Override
    public void moveBreed() {
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

                if (symbolsInCurrentCoord.indexOf("s") != -1 || symbolsInCurrentCoord.indexOf("S") != -1) {
                    possiblePositions[i] = new Position(currentX + i, currentY + j);
                } else {
                    continue;
                }
            }
        }
        //  TODO проверка на пустоту
        this.setPosition(possiblePositions[0 + (int) (Math.random() * possiblePositions.length)]);¸
    }

    @Override
    public void upgrade() {
        // хуй знает работает или нет
        MyWorldController.world.get(this.getPosition()).add(new SymbolCapitalS(this));
    }
}
