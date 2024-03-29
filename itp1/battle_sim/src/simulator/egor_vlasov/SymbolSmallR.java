package simulator.egor_vlasov;

import simulator.do_not_change.*;
import simulator.egor_vlasov.*;
import simulator.egor_vlasov.Util;
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;

public class SymbolSmallR extends Symbol implements Passive, SmallCase {

    public final int UPGRADE_ITERATIONS = Util.getRandomNumber(30, 50);

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    public SymbolSmallR(Position position, int sightDistance) {
        this.idSymbol = Symbol.COUNT_SYMBOLS++;
        this.position = position;
        this.sightDistance = sightDistance;
        this.numberIterationsAlive = 0;
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
        List<Position> truePossiblePositions = new ArrayList();

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

        for (Position position : possiblePositions) {
            LinkedList symbolsInCurrentCoord = MyWorldController.world.get(position);

            if (!Util.hasSymbol(symbolsInCurrentCoord, SymbolCapitalS.class)
                    && !Util.hasSymbol(symbolsInCurrentCoord, SymbolSmallS.class)
                    && !Util.hasSymbol(symbolsInCurrentCoord, SymbolCapitalP.class)
                    && !Util.hasSymbol(symbolsInCurrentCoord, SymbolSmallP.class)) {
                truePossiblePositions.add(position);
            } else {
                continue;
            }
        }

        if (truePossiblePositions.size() > 0) {
            this.setPosition(truePossiblePositions.get(Util.getRandomNumber(0, truePossiblePositions.size() - 1)));
        }
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
        List<Position> truePossiblePositions = new ArrayList();

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

        for (Position position : possiblePositions) {
            LinkedList symbolsInCurrentCoord = MyWorldController.world.get(position);

            if (Util.hasSymbol(symbolsInCurrentCoord, SymbolCapitalR.class)
                    || Util.hasSymbol(symbolsInCurrentCoord, SymbolSmallR.class)) {
                truePossiblePositions.add(position);
            } else {
                continue;
            }
        }

        if (truePossiblePositions.size() > 0) {
            this.setPosition(truePossiblePositions.get(Util.getRandomNumber(0, truePossiblePositions.size() - 1)));
        }
    }

    @Override
    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    public void upgrade() {
        // хуй знает работает или нет
        MyWorldController.world.get(this.getPosition()).add(new SymbolCapitalR(this));
    }
}
