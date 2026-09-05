function CacheNode({
    item,
    showFrequency = false,
    isActive = false,
    isEvicted = false,
}) {
    return (
        <div
            className={`cache-node ${
                isActive ? "node-active" : ""
            } ${isEvicted ? "node-evicted" : ""}`}
        >
            <div className="node-key">
                {item.key}
            </div>

            <div className="node-value">
                {item.value}
            </div>

            {showFrequency && (
                <div className="frequency">
                    Freq: {item.frequency}
                </div>
            )}
        </div>
    );
}

export default CacheNode;