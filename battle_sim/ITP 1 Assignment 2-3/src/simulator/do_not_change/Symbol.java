package simulator.do_not_change;

public abstract class Symbol {

	/**
	 * Unique for each symbol
	 */
	private int idSymbol;
	private Position position;
	private int sightDistance;
	private int numberIterationsAlive;

	public int getIdSymbol() {
		return idSymbol;
	}

	public Position getPosition() {
		return position;
	}

	public void setPosition(Position position) {
		this.position = position;
	}

	public int getSightDistance() {
		return sightDistance;
	}

	public int getNumberIterationsAlive() {
		return numberIterationsAlive;
	}

	/**
	 * Increase the number of iterations that symbol has been alive.
	 */
	public void becomeOlder() {
		this.numberIterationsAlive++;
	}

	// Moving randomly within its sightDistance
	public abstract void move();

	// The last words before dying
	public abstract void die();

}
