import { useLayoutEffect, useRef } from "react";
import CacheNode from "./CacheNode";

function CacheVisualizer({
    policy,
    cacheState,
    capacity,
    lastOperation,
    evictedItem,
}) {
    const items = cacheState.items || [];

    // Store DOM elements for each cache node
    const nodeRefs = useRef({});

    // Store previous positions
    const previousPositions = useRef({});

    // --------------------------------
    // LRU / FIFO movement animation
    // --------------------------------

    useLayoutEffect(() => {
        if (policy === "LFU") {
            return;
        }

        const currentPositions = {};

        items.forEach((item) => {
            const element = nodeRefs.current[item.key];

            if (!element) {
                return;
            }

            const rect = element.getBoundingClientRect();

            currentPositions[item.key] = {
                left: rect.left,
                top: rect.top,
            };
        });

        Object.keys(currentPositions).forEach((key) => {
            const previous =
                previousPositions.current[key];

            const current =
                currentPositions[key];

            if (!previous) {
                return;
            }

            const deltaX =
                previous.left - current.left;

            const deltaY =
                previous.top - current.top;

            if (deltaX === 0 && deltaY === 0) {
                return;
            }

            const element =
                nodeRefs.current[key];

            if (!element) {
                return;
            }

            // Move instantly to old position
            element.style.transition = "none";

            element.style.transform = `
                translate(${deltaX}px, ${deltaY}px)
            `;

            // Force browser to apply the transform
            element.getBoundingClientRect();

            // Animate to the new position
            requestAnimationFrame(() => {
                element.style.transition =
                    "transform 450ms cubic-bezier(0.2, 0.8, 0.2, 1)";

                element.style.transform =
                    "translate(0, 0)";
            });
        });

        previousPositions.current =
            currentPositions;

    }, [items, policy]);

    // --------------------------------
    // Active node
    // --------------------------------

    const isActiveNode = (item) => {
        if (!lastOperation) {
            return false;
        }

        return (
            lastOperation.key === item.key &&
            lastOperation.status === "HIT"
        );
    };

    // --------------------------------
    // Linked List
    // --------------------------------

    const renderLinkedList = () => {
        return (
            <div className="linked-list-container">

                <div className="list-label">
                    HEAD
                </div>

                <div className="linked-list">

                    {items.length === 0 ? (
                        <div className="empty-cache">
                            Cache is empty
                        </div>
                    ) : (
                        items.map((item, index) => (
                            <div
                                className="node-wrapper"
                                key={item.key}
                                ref={(element) => {
                                    if (element) {
                                        nodeRefs.current[
                                            item.key
                                        ] = element;
                                    } else {
                                        delete nodeRefs.current[
                                            item.key
                                        ];
                                    }
                                }}
                            >
                                <CacheNode
                                    item={item}
                                    isActive={isActiveNode(
                                        item
                                    )}
                                />

                                {index <
                                    items.length - 1 && (
                                    <div className="arrow">
                                        →
                                    </div>
                                )}
                            </div>
                        ))
                    )}

                </div>

                <div className="list-label">
                    TAIL
                </div>

                {evictedItem && (
                    <div className="eviction-preview">
                        <span className="eviction-label">
                            EVICTING
                        </span>

                        <CacheNode
                            item={evictedItem}
                            isEvicted
                        />
                    </div>
                )}

            </div>
        );
    };

    // --------------------------------
    // LFU
    // --------------------------------

    const renderLFU = () => {
        const frequencyMap = {};

        items.forEach((item) => {
            const frequency =
                item.frequency || 1;

            if (!frequencyMap[frequency]) {
                frequencyMap[frequency] = [];
            }

            frequencyMap[frequency].push(item);
        });

        const frequencies = Object.keys(
            frequencyMap
        )
            .map(Number)
            .sort((a, b) => a - b);

        if (items.length === 0) {
            return (
                <div className="empty-cache">
                    Cache is empty
                </div>
            );
        }

        return (
            <div className="lfu-container">

                {frequencies.map((frequency) => (
                    <div
                        className="frequency-group"
                        key={frequency}
                    >
                        <div className="frequency-title">
                            Frequency {frequency}
                        </div>

                        <div className="frequency-nodes">

                            {frequencyMap[
                                frequency
                            ].map((item) => (
                                <CacheNode
                                    key={item.key}
                                    item={item}
                                    showFrequency
                                    isActive={isActiveNode(
                                        item
                                    )}
                                />
                            ))}

                        </div>
                    </div>
                ))}

            </div>
        );
    };

    return (
        <section className="card visualizer-card">

            <div className="section-header">

                <div>
                    <h2>
                        Cache Visualization
                    </h2>

                    <p>
                        Current Policy:{" "}
                        <strong>{policy}</strong>
                    </p>
                </div>

                <div className="capacity-indicator">
                    {items.length} / {capacity}
                </div>

            </div>

            {policy === "LFU"
                ? renderLFU()
                : renderLinkedList()}

        </section>
    );
}

export default CacheVisualizer;