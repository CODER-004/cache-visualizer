function OperationLog({ logs }) {
    return (
        <section className="card log-card">

            <div className="section-header">
                <h2>Operation Log</h2>

                <span>
                    {logs.length} operations
                </span>
            </div>

            {logs.length === 0 ? (
                <div className="empty-log">
                    No operations yet
                </div>
            ) : (
                <div className="log-list">

                    {logs.map((log) => (
                        <div
                            className={`log-item ${log.type}`}
                            key={log.id}
                        >
                            <span className="log-time">
                                {log.time}
                            </span>

                            <span>
                                {log.message}
                            </span>
                        </div>
                    ))}

                </div>
            )}

        </section>
    );
}

export default OperationLog;