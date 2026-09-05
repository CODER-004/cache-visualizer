function Stats({
    cacheSize,
    capacity,
    hits,
    misses,
    evictions,
}) {
    return (
        <section className="stats-grid">

            <div className="stat-card">
                <span>Cache Size</span>
                <strong>{cacheSize}</strong>
            </div>

            <div className="stat-card">
                <span>Capacity</span>
                <strong>{capacity}</strong>
            </div>

            <div className="stat-card">
                <span>Hits</span>
                <strong>{hits}</strong>
            </div>

            <div className="stat-card">
                <span>Misses</span>
                <strong>{misses}</strong>
            </div>

            <div className="stat-card">
                <span>Evictions</span>
                <strong>{evictions}</strong>
            </div>

        </section>
    );
}

export default Stats;