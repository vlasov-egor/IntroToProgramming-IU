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

        for (int x = 0; x <= 10; x++) {
            for (int y = 0; y <= 10; y++) {
                MyWorldController.world.put(new Position(y, x), new LinkedList());
            }
        }

        //  generator
        for (int i = 0; i < 0 + (int) (Math.random() * 10); i++) {
            int randomX = 0 + (int) (Math.random() * 9);
            int randomY = 0 + (int) (Math.random() * 9);
            int randomSightDistance = 0 + (int) (Math.random() * 5);

            char[] letters = { CAPITAL_R, CAPITAL_P, CAPITAL_S, SMALL_R, SMALL_P, SMALL_S };
            char randomLetter = letters[0 + (int) (Math.random() * 5)];

            Position newPosition = new Position(randomX, randomY);
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

    //  мувы хуювы
    public void symbolsMove(List<Symbol> symbols) {
        for (Symbol symbol : symbols) {
            symbol.move();
            MyWorldController.world.get(symbol.getPosition()).add(symbol);
        }
    }

    public void symbolsDie(List<Symbol> symbols) {
        for (Symbol symbol : symbols) {
            symbol.die();
        }
    }

    public void smallCaseUpgrade(List<SmallCase> symbols) {
        // типо должен их возводить в новый ранг ебать
        for (SmallCase symbol : symbols) {
            symbol.upgrade();
        }
    }

    public void capitalCaseJump(List<CapitalCase> symbols) {
        // прыгает как ебанный кенгуру хуй знает куда
        for (CapitalCase symbol : symbols) {
            symbol.jump();
            MyWorldController.world.get(((Symbol)symbol).getPosition()).add((Symbol)symbol);
        }
    }

    public void passiveEscape(List<Passive> symbols) {
        // съебывает вообще от всего
        for (Passive symbol : symbols) {
            symbol.escape();
            MyWorldController.world.get(((Symbol)symbol).getPosition()).add((Symbol)symbol);
        }
    }

    public void passiveBreed(List<Passive> symbols) {
        // идет к своим ровным пацикам
        for (Passive symbol : symbols) {
            symbol.moveBreed();
            MyWorldController.world.get(((Symbol)symbol).getPosition()).add((Symbol)symbol);
        }
    }

    public void aggressiveAttackSmart(List<Aggressive> symbols) {
        // ебашит умно против детей
        for (Aggressive symbol : symbols) {
            symbol.attackSmart();
            MyWorldController.world.get(((Symbol)symbol).getPosition()).add((Symbol)symbol);
        }
    }

    public String plotWorld() {
        // выводит всю эту хуйню в 10х10 стринг
        return "";
    }
}
