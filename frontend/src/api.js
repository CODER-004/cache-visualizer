const BASE_URL = "http://localhost:8080";

export async function putCache(key, value) {
    const response = await fetch(`${BASE_URL}/cache/put`, {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({
            key,
            value,
        }),
    });

    return response.json();
}


export async function getCache(key) {
    const response = await fetch(
        `${BASE_URL}/cache/get/${encodeURIComponent(key)}`
    );

    return response.json();
}


export async function getCacheState() {
    const response = await fetch(`${BASE_URL}/cache/state`);

    return response.json();
}


export async function changePolicy(policy) {
    const response = await fetch(`${BASE_URL}/cache/policy`, {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({
            policy,
        }),
    });

    return response.json();
}


export async function resetCache() {
    const response = await fetch(`${BASE_URL}/cache/reset`, {
        method: "POST",
    });

    return response.json();
}