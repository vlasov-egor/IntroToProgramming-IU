package simulator.egor_vlasov;

import simulator.do_not_change.WorldController;
import simulator.do_not_change.Symbol;
import simulator.do_not_change.Passive;
import simulator.do_not_change.Aggressive;
import simulator.do_not_change.CapitalCase;
import simulator.do_not_change.SmallCase;
import java.util.List;
import java.util.HashMap;

public class MyWorldController extends WorldController {
    public static int lastId;
    // TODO ебануть генератор, который раз в n итераций ебашит нового уебка
    // Нахер не надо. Генерить надо адын раз

    public MyWorldController() {
        super();
        MyWorldController.world = new HashMap();
        MyWorldController.lastId = 0;
        // x = random;
        // y = random;
        // type = random;
        
    }
    
    public void symbolsMove(List<Symbol> symbols) {
        for (Symbol symbol: symbols) {
            symbol.move();
            MyWorldController.world.get(symbol.getPosition()).add(symbol);
        } 
    }

    public void symbolsDie(List<Symbol> symbols) {
        for (Symbol symbol: symbols) {
            symbol.die();
        }
    }

    public void smallCaseUpgrade(List<SmallCase> symbols) {
        //  типо должен их возводить в новый ранг ебать
        for (SmallCase symbol: symbols) {
            symbol.upgrade();
        } 
    }

    public void capitalCaseJump(List<CapitalCase> symbols) {
        //  прыгает как ебанный кенгуру хуй знает куда
        for (CapitalCase symbol: symbols) {
            symbol.jump();
            MyWorldController.world.get(symbol.getPosition()).add(symbol);
        } 
    }

    public void passiveEscape(List<Passive> symbols) {
        //  съебывает вообще от всего
        for (Passive symbol: symbols) {
            symbol.escape();
            MyWorldController.world.get(symbol.getPosition()).add(symbol);
        } 
    }

    public void passiveBreed(List<Passive> symbols) {
        //  идет к своим ровным пацикам
        for (Passive symbol: symbols) {
            symbol.moveBreed();
            MyWorldController.world.get(symbol.getPosition()).add(symbol);
        } 
    }

    public void aggressiveAttackSmart(List<Aggressive> symbols) {
        //  ебашит умно против детей
        for (Aggressive symbol: symbols) {
            symbol.attackSmart();
            MyWorldController.world.get(symbol.getPosition()).add(symbol);
        } 
    }

    public String plotWorld() {
        //  выводит всю эту хуйню в 10х10 стринг
        return "";
    }
}
