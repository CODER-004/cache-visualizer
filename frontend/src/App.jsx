import { useEffect, useState } from "react";

import {
    putCache,
    getCache,
    getCacheState,
    changePolicy,
    resetCache,
} from "./api";

import CacheControls from "./components/CacheControls";
import CacheVisualizer from "./components/CacheVisualizer";
import Stats from "./components/Stats";
import OperationLog from "./components/OperationLog";

import "./App.css";

function App() {
    const [policy, setPolicy] = useState("LRU");
    const [capacity] = useState(5);

    const [key, setKey] = useState("");
    const [value, setValue] = useState("");

    const [cacheState, setCacheState] = useState({
        items: [],
    });

    const [logs, setLogs] = useState([]);

    const [hits, setHits] = useState(0);
    const [misses, setMisses] = useState(0);
    const [evictions, setEvictions] = useState(0);
    const [evictedItem, setEvictedItem] = useState(null);
    const [lastOperation, setLastOperation] = useState(null);

    const refreshCache = async () => {
        try {
            const data = await getCacheState();

            setCacheState(data);

            if (data.policy) {
                setPolicy(data.policy);
            }
        } catch (error) {
            console.error(
                "Failed to fetch cache state:",
                error
            );
        }
    };

    useEffect(() => {
        refreshCache();
    }, []);

    const addLog = (message, type = "normal") => {
        setLogs((prev) => [
            {
                id: Date.now(),
                message,
                type,
                time: new Date().toLocaleTimeString(),
            },
            ...prev,
        ]);
    };

    const handlePut = async () => {
        if (!key.trim() || !value.trim()) {
            return;
        }

        try {
            const previousItems =
                cacheState.items || [];

            await putCache(key, value);

            const newState =
                await getCacheState();

            setCacheState(newState);

            const newKeys =
                newState.items?.map(
                    (item) => item.key
                ) || [];

            const removedItem =
                previousItems.find(
                    (item) =>
                        !newKeys.includes(item.key)
                );

            const wasEvicted =
                removedItem !== undefined;

            if (wasEvicted) {

                setEvictedItem(removedItem);

                setTimeout(() => {
                    setEvictedItem(null);
                }, 700);

                setEvictions(
                    (prev) => prev + 1
                );

                addLog(
                    `PUT ${key} = ${value} → EVICTION`,
                    "eviction"
                );

            } else {

                setEvictedItem(null);

                addLog(
                    `PUT ${key} = ${value}`,
                    "put"
                );
            }

            setLastOperation({
                type: "PUT",
                key,
                value,
                status: "SUCCESS",
            });

            setKey("");
            setValue("");

        } catch (error) {
            console.error(error);

            addLog(
                `PUT ${key} failed`,
                "error"
            );
        }
    };

    const handleGet = async () => {
        if (!key.trim()) {
            return;
        }

        try {
            const response = await getCache(key);

            if (response.hit) {

                setHits(
                    (prev) => prev + 1
                );

                setLastOperation({
                    type: "GET",
                    key,
                    value: response.value,
                    status: "HIT",
                });

                addLog(
                    `GET ${key} → HIT (${response.value})`,
                    "hit"
                );

            } else {

                setMisses(
                    (prev) => prev + 1
                );

                setLastOperation({
                    type: "GET",
                    key,
                    value: null,
                    status: "MISS",
                });

                addLog(
                    `GET ${key} → MISS`,
                    "miss"
                );
            }

            await refreshCache();

            setKey("");

        } catch (error) {
            console.error(error);

            addLog(
                `GET ${key} failed`,
                "error"
            );
        }
    };

    const handlePolicyChange = async (event) => {
        const newPolicy =
            event.target.value;

        try {
            await changePolicy(
                newPolicy
            );

            setPolicy(newPolicy);

            addLog(
                `Eviction policy changed → ${newPolicy}`,
                "policy"
            );

            await refreshCache();

        } catch (error) {
            console.error(error);
        }
    };

    const handleReset = async () => {
        try {
            await resetCache();

            setHits(0);
            setMisses(0);
            setEvictions(0);
            setEvictedItem(null);

            setLogs([]);
            setLastOperation(null);

            await refreshCache();

        } catch (error) {
            console.error(error);
        }
    };

    return (
        <div className="app">

            <header className="header">
                <div>
                    <h1>
                        Cache Visualizer
                    </h1>

                    <p>
                        Visualize LRU, LFU and FIFO
                        cache eviction strategies
                    </p>
                </div>
            </header>

            <CacheControls
                policy={policy}
                capacity={capacity}
                keyValue={key}
                value={value}
                setKey={setKey}
                setValue={setValue}
                onPolicyChange={
                    handlePolicyChange
                }
                onPut={handlePut}
                onGet={handleGet}
                onReset={handleReset}
            />

            <Stats
                cacheSize={
                    cacheState.items?.length || 0
                }
                capacity={capacity}
                hits={hits}
                misses={misses}
                evictions={evictions}
            />

            <CacheVisualizer
                policy={policy}
                cacheState={cacheState}
                capacity={capacity}
                lastOperation={lastOperation}
                evictedItem={evictedItem}
            />

            {lastOperation && (
                <section className="card operation-card">

                    <h2>
                        Last Operation
                    </h2>

                    <div className="operation-details">

                        <span className="operation-type">
                            {lastOperation.type}
                        </span>

                        <span>
                            Key:{" "}
                            <strong>
                                {lastOperation.key}
                            </strong>
                        </span>

                        {lastOperation.value !== null &&
                            lastOperation.value !==
                                undefined && (
                                <span>
                                    Value:{" "}
                                    <strong>
                                        {
                                            lastOperation.value
                                        }
                                    </strong>
                                </span>
                            )}

                        <span
                            className={`operation-status ${lastOperation.status.toLowerCase()}`}
                        >
                            {lastOperation.status}
                        </span>

                    </div>

                </section>
            )}

            <OperationLog logs={logs} />

        </div>
    );
}

export default App;