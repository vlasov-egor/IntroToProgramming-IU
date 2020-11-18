package simulator.egor_vlasov;

import simulator.do_not_change.*;
import simulator.egor_vlasov.*;
import java.util.LinkedList;
import java.util.List;
import simulator.egor_vlasov.Util;
import java.util.ArrayList;

public class SymbolCapitalP extends Symbol implements Passive, CapitalCase {
    public final int DIE_ITERATIONS = Util.getRandomNumber(70, 100);

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    public SymbolCapitalP(Position position, int sightDistance) {
        this.idSymbol = Symbol.COUNT_SYMBOLS++;
        this.position = position;
        this.sightDistance = sightDistance;
        this.numberIterationsAlive = 0;
    }

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    public SymbolCapitalP(SymbolSmallP small) {
        this.idSymbol = small.getIdSymbol();
        this.position = small.getPosition();
        this.sightDistance = small.getSightDistance() + 1;
        this.numberIterationsAlive = small.getNumberIterationsAlive() + 1;
    }

    @Override
    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
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
    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    public void die() {

    }

    @Override
    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
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
                        && !Util.<SymbolCapitalR>hasSymbol(symbolsInCurrentCoord)
                        && !Util.<SymbolSmallR>hasSymbol(symbolsInCurrentCoord)) {
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
    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
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

                if (Util.<SymbolSmallP>hasSymbol(symbolsInCurrentCoord)
                        || Util.<SymbolCapitalP>hasSymbol(symbolsInCurrentCoord)) {
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
    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    public void jump() {
        System.out.println("jump");
        System.out.println(this.getPosition());
        int randomX = Util.getRandomNumber(0, 9);
        int randomY = Util.getRandomNumber(0, 9);

        Position newPosition = new Position(randomY, randomX);
        this.setPosition(newPosition);
    }
}
