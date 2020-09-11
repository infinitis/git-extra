const assert = require('assert');
const util = require('util');

const exec = util.promisify(require('child_process').exec);

const workdir = "working";

const reset_env = async() => {
	await assert.doesNotReject(async() => await exec(`rm -rf ${workdir}`,{cwd:"/home/node/"}));
};

const setup_env = async() => {
	await assert.doesNotReject(async() => await exec(`git init ${workdir}`,{cwd:"/home/node/"}));
	await assert.doesNotReject(async() => await exec('git config --local user.email "test@test.com"',{cwd:"/home/node/working"}));
	await assert.doesNotReject(async() => await exec('git config --local user.name "test"',{cwd:"/home/node/working"}));
	await assert.doesNotReject(async() => await exec(`git config --local core.editor "sh -c 'echo \\"hello\\" >> \\"\\$0\\"'"`,{cwd:"/home/node/working"}));
	await assert.doesNotReject(async() => await exec(`echo "test" > test.txt`,{cwd:"/home/node/working"}));
	await assert.doesNotReject(async() => await exec(`git add -A`,{cwd:"/home/node/working"}));
	await assert.doesNotReject(async() => await exec(`git commit -a -m "..."`,{cwd:"/home/node/working"}));
};

module.exports = {
	reset_env,
	setup_env
};