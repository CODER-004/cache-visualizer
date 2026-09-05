function CacheControls({
    policy,
    capacity,
    keyValue,
    value,
    setKey,
    setValue,
    onPolicyChange,
    onPut,
    onGet,
    onReset,
}) {
    return (
        <section className="card controls-card">
            <h2>Cache Controls</h2>

            <div className="controls">

                <div className="input-group">
                    <label>Policy</label>

                    <select
                        value={policy}
                        onChange={onPolicyChange}
                    >
                        <option value="LRU">LRU</option>
                        <option value="LFU">LFU</option>
                        <option value="FIFO">FIFO</option>
                    </select>
                </div>

                <div className="input-group">
                    <label>Capacity</label>

                    <input
                        type="number"
                        value={capacity}
                        disabled
                    />
                </div>

                <div className="input-group">
                    <label>Key</label>

                    <input
                        type="text"
                        placeholder="Enter key"
                        value={keyValue}
                        onChange={(e) =>
                            setKey(e.target.value)
                        }
                    />
                </div>

                <div className="input-group">
                    <label>Value</label>

                    <input
                        type="text"
                        placeholder="Enter value"
                        value={value}
                        onChange={(e) =>
                            setValue(e.target.value)
                        }
                    />
                </div>

                <div className="button-group">

                    <button
                        className="put-button"
                        onClick={onPut}
                    >
                        PUT
                    </button>

                    <button
                        className="get-button"
                        onClick={onGet}
                    >
                        GET
                    </button>

                </div>
            </div>

            <button
                className="reset-button control-reset"
                onClick={onReset}
            >
                Reset Cache
            </button>
        </section>
    );
}

export default CacheControls;