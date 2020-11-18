package simulator.egor_vlasov;

import simulator.do_not_change.*;
import simulator.egor_vlasov.*;
import simulator.egor_vlasov.Util;
import java.util.LinkedList;
import java.util.List;

public class SymbolSmallS extends Symbol implements Passive, SmallCase {

    public final int UPGRADE_ITERATIONS = 50;

    public SymbolSmallS(Position position, int sightDistance) {
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
    public void escape() {
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

                if (!Util.<SymbolCapitalR>hasSymbol(symbolsInCurrentCoord)
                        && !Util.<SymbolSmallR>hasSymbol(symbolsInCurrentCoord)
                        && !Util.<SymbolCapitalP>hasSymbol(symbolsInCurrentCoord)
                        && !Util.<SymbolSmallP>hasSymbol(symbolsInCurrentCoord)) {
                    possiblePositions.add(new Position(currentY + i, currentX + j));
                } else {
                    continue;
                }
            }
        }
        // TODO проверка на пустоту
        this.setPosition(possiblePositions[Util.getRandomNumber(0, possiblePositions.size())]);
    }

    @Override
    public void moveBreed() {
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

                if (Util.<SymbolCapitalS>hasSymbol(symbolsInCurrentCoord)
                        || Util.<SymbolSmallS>hasSymbol(symbolsInCurrentCoord)) {
                    possiblePositions.add(new Position(currentY + i, currentX + j));
                } else {
                    continue;
                }
            }
        }
        // TODO проверка на пустоту
        this.setPosition(possiblePositions[Util.getRandomNumber(0, possiblePositions.size())]);
    }

    @Override
    public void upgrade() {
        // хуй знает работает или нет
        MyWorldController.world.get(this.getPosition()).add(new SymbolCapitalS(this));
    }
}
