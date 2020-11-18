package simulator.egor_vlasov;

import simulator.do_not_change.*;
import simulator.egor_vlasov.*;
import simulator.egor_vlasov.Util;
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;

public class SymbolSmallR extends Symbol implements Passive, SmallCase {

    public final int UPGRADE_ITERATIONS = Util.getRandomNumber(30, 50);;

    public SymbolSmallR(Position position, int sightDistance) {
        this.idSymbol = Symbol.COUNT_SYMBOLS++;
        this.position = position;
        this.sightDistance = sightDistance;
        this.numberIterationsAlive = 0;
    }

    @Override
    public void move() {
        int currentX = this.getPosition().column;
        int currentY = this.getPosition().row;
        List<Position> possiblePositions = new ArrayList();

        for (int i = 0; i <= sightDistance; i++) {
            for (int j = 0; j <= sightDistance; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                if (currentY + i < MyWorldController.MAX_ROWS && currentX + j < MyWorldController.MAX_COLS) {
                    possiblePositions.add(new Position(currentY + i, currentX + j));
                }
                if (currentY + i < MyWorldController.MAX_ROWS && currentX - j >= 0) {
                    possiblePositions.add(new Position(currentY + i, currentX - j));
                }
                if (currentY - i >= 0 && currentX - j >= 0) {
                    possiblePositions.add(new Position(currentY - i, currentX - j));
                }
                if (currentY - i >= 0 && currentX + j < MyWorldController.MAX_COLS) {
                    possiblePositions.add(new Position(currentY - i, currentX + j));
                }
            }
        }

        this.setPosition(possiblePositions.get(Util.getRandomNumber(0, possiblePositions.size() - 1)));
    }

    @Override
    public void die() {
        
    }

    @Override
    public void escape() {
        int currentX = this.getPosition().column;
        int currentY = this.getPosition().row;
        List<Position> possiblePositions = new ArrayList();

        for (int i = 0; i <= sightDistance; i++) {
            for (int j = 0; j <= sightDistance; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                // так заебись? или хуево?
                LinkedList symbolsInCurrentCoord = MyWorldController.world
                        .get(new Position(currentY + i, currentX + j));

                if (!Util.<SymbolCapitalS>hasSymbol(symbolsInCurrentCoord)
                        && !Util.<SymbolSmallS>hasSymbol(symbolsInCurrentCoord)
                        && !Util.<SymbolCapitalP>hasSymbol(symbolsInCurrentCoord)
                        && !Util.<SymbolSmallP>hasSymbol(symbolsInCurrentCoord)) {
                    if (currentX + i < MyWorldController.MAX_COLS && currentY + j < MyWorldController.MAX_ROWS) {
                        possiblePositions.add(new Position(currentY + i, currentX + j));
                    }
                } else {
                    continue;
                }
            }
        }
        // TODO проверка на пустоту
        this.setPosition(possiblePositions.get(Util.getRandomNumber(0, possiblePositions.size() - 1)));
    }

    @Override
    public void moveBreed() {
        int currentX = this.getPosition().column;
        int currentY = this.getPosition().row;
        List<Position> possiblePositions = new ArrayList();

        for (int i = 0; i <= sightDistance; i++) {
            for (int j = 0; j <= sightDistance; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                // так заебись? или хуево?
                LinkedList symbolsInCurrentCoord = MyWorldController.world
                        .get(new Position(currentY + i, currentX + j));

                if (Util.<SymbolCapitalR>hasSymbol(symbolsInCurrentCoord)
                        || Util.<SymbolSmallR>hasSymbol(symbolsInCurrentCoord)) {
                    if (currentX + i < MyWorldController.MAX_COLS && currentY + j < MyWorldController.MAX_ROWS) {
                        possiblePositions.add(new Position(currentY + i, currentX + j));
                    }
                } else {
                    continue;
                }
            }
        }
        // TODO проверка на пустоту
        this.setPosition(possiblePositions.get(Util.getRandomNumber(0, possiblePositions.size() - 1)));
    }

    @Override
    public void upgrade() {
        // хуй знает работает или нет
        MyWorldController.world.get(this.getPosition()).add(new SymbolCapitalR(this));
    }
}
