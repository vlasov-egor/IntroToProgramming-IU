package simulator.egor_vlasov;

import simulator.do_not_change.WorldController;
import simulator.do_not_change.Symbol;
import simulator.do_not_change.Passive;
import simulator.do_not_change.Position;
import simulator.do_not_change.Aggressive;
import simulator.do_not_change.CapitalCase;
import simulator.do_not_change.SmallCase;
import simulator.egor_vlasov.*;
import java.util.List;
import java.util.HashMap;
import java.util.Random;
import java.util.LinkedList;

public class MyWorldController extends WorldController {
    public MyWorldController() {
        super();
        MyWorldController.world = new HashMap();

        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                MyWorldController.world.put(new Position(y, x), new LinkedList());
            }
        }

        //  Creating random Symbols in random positions
        for (int i = 0; i < Util.getRandomNumber(50, 100); i++) {
            int randomX = Util.getRandomNumber(0, 9);
            int randomY = Util.getRandomNumber(0, 9);
            int randomSightDistance = Util.getRandomNumber(1, 5);

            char[] letters = { CAPITAL_R, CAPITAL_P, CAPITAL_S, SMALL_R, SMALL_P, SMALL_S };
            char randomLetter = letters[Util.getRandomNumber(0, 5)];

            Position newPosition = new Position(randomY, randomX);
            Symbol newSymbol = null;
            switch (randomLetter) {
                case CAPITAL_R:
                    newSymbol = new SymbolCapitalR(newPosition, randomSightDistance);
                    break;
                case CAPITAL_P:
                    newSymbol = new SymbolCapitalP(newPosition, randomSightDistance);
                    break;
                case CAPITAL_S:
                    newSymbol = new SymbolCapitalS(newPosition, randomSightDistance);
                    break;
                case SMALL_R:
                    newSymbol = new SymbolSmallR(newPosition, randomSightDistance);
                    break;
                case SMALL_P:
                    newSymbol = new SymbolSmallP(newPosition, randomSightDistance);
                    break;
                case SMALL_S:
                    newSymbol = new SymbolSmallS(newPosition, randomSightDistance);
                    break;
            }

            MyWorldController.world.get(newPosition).add(newSymbol);
        }
    }

    //  symbolsMove
    public void symbolsMove(List<Symbol> symbols) {
        for (Symbol symbol : symbols) {
            symbol.move();
            MyWorldController.world.get(symbol.getPosition()).add(symbol);
        }
    }

    //  symbolsDie
    public void symbolsDie(List<Symbol> symbols) {
        for (Symbol symbol : symbols) {
            symbol.die();
        }
    }

    //  smallCaseUpgrade
    public void smallCaseUpgrade(List<SmallCase> symbols) {
        for (SmallCase symbol : symbols) {
            symbol.upgrade();
        }
    }

    //  capitalCaseJump
    public void capitalCaseJump(List<CapitalCase> symbols) {
        for (CapitalCase symbol : symbols) {
            symbol.jump();
            MyWorldController.world.get(((Symbol)symbol).getPosition()).add((Symbol)symbol);
        }
    }

    //  passiveEscape
    public void passiveEscape(List<Passive> symbols) {
        for (Passive symbol : symbols) {
            symbol.escape();
            MyWorldController.world.get(((Symbol)symbol).getPosition()).add((Symbol)symbol);
        }
    }

    //  passiveBreed
    public void passiveBreed(List<Passive> symbols) {
        for (Passive symbol : symbols) {
            symbol.moveBreed();
            MyWorldController.world.get(((Symbol)symbol).getPosition()).add((Symbol)symbol);
        }
    }

    //  aggressiveAttackSmart
    public void aggressiveAttackSmart(List<Aggressive> symbols) {
        for (Aggressive symbol : symbols) {
            symbol.attackSmart();
            MyWorldController.world.get(((Symbol)symbol).getPosition()).add((Symbol)symbol);
        }
    }

    //  plotWorld
    public String plotWorld() {
        return "";
    }
}
