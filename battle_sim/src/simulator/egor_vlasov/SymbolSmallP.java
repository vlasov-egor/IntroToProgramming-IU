package simulator.egor_vlasov;

import simulator.do_not_change.*;
import simulator.egor_vlasov.*;
import simulator.egor_vlasov.Util;
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;

public class SymbolSmallP extends Symbol implements Aggressive, SmallCase {

    public final int UPGRADE_ITERATIONS = Util.getRandomNumber(30, 50);;

    /**
     * Return the Manhattan distance between this position and another object of
     * Position
     * 
     * @param other
     * @return
     */
    public SymbolSmallP(Position position, int sightDistance) {
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
    public void attackSmart() {
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

                if (!Util.hasSymbol(symbolsInCurrentCoord, SymbolSmallR.class)
                        && !Util.hasSymbol(symbolsInCurrentCoord, SymbolCapitalR.class)) {
                    continue;
                } else {
                    if (currentX + i < MyWorldController.MAX_COLS && currentY + j < MyWorldController.MAX_ROWS) {
                        possiblePositions.add(new Position(currentY + i, currentX + j));
                    }
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
    public void upgrade() {
        MyWorldController.world.get(this.getPosition()).add(new SymbolCapitalP(this));
    }
}
